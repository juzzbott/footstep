#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QString>
#include <QStringBuilder>
#include <QStandardPaths>

#include "preferences.h"
#include "ui_preferences.h"
#include "core/config/footstepconfig.h"
#include "core/config/footstepconfigloader.h"

Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);

    FootstepConfigLoader configLoader = FootstepConfigLoader();
    _config = configLoader.config();

    // Set the values of the controls on the form
    ui->_txtProfileDirectory->setText(_config->profileDirectory());

    if (_config->coordinateType() == FootstepConfig::Decimal) {
        ui->_rdoDecimal->setChecked(true);
    } else {
        ui->_rdoDegrees->setChecked(true);
    }

    if (_config->mapTileCacheType() == FootstepConfig::DiskMemoryCache) {
        ui->_rdoDiskMemoryCache->setChecked(true);
    } else {
        ui->_rdoNoCache->setChecked(true);
    }

    ui->_spnCacheExpiry->setValue(_config->mapTileExpiry());

}

Preferences::~Preferences()
{
    delete ui;
}

//
// Slots
//

void Preferences::browseProfileDirectory() {

    // Create the open file dialog
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setOption(QFileDialog::ShowDirsOnly);

    // Read the directory name from the file dialog
    QString directory;
    if (dialog.exec() == QDialog::Accepted) {
        directory = dialog.selectedFiles()[0];
    }

    // Set the textbox value with the path selected.
    ui->_txtProfileDirectory->setText(directory);

}

void Preferences::accept() {

    QString newProfileDir = ui->_txtProfileDirectory->text();

    // If the profile directory has changed, and the new folder is not empty, show the user a warning message.
    if (!QString::compare(_config->originalProfileDirectory(), newProfileDir, Qt::CaseInsensitive)) {

        // we don't care if the directory is empty.
        if(QDir(ui->_txtProfileDirectory->text()).entryInfoList(QDir::NoDotAndDotDot|QDir::AllEntries).count() == 0) {

            // Show the alert that the direcotry exists (and has things in it.
            QMessageBox confirmNewDir;
            confirmNewDir.setText("The directory already exists.");
            confirmNewDir.setInformativeText("The directory '" % ui->_txtProfileDirectory->text() % "' aready exists. If you choose to continue, the contents of this folder will be deleted.");
            confirmNewDir.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            confirmNewDir.setDefaultButton(QMessageBox::Cancel);
            confirmNewDir.setIcon(QMessageBox::Warning);
            int result = confirmNewDir.exec();

            // If the user cancelled, just return
            if (result == QMessageBox::Cancel) {
                return;
            }

        }

    }

    // Set the values of the dialog window
    _config->setProfileDirectory(ui->_txtProfileDirectory->text());
    _config->setCoordinateType((ui->_rdoDecimal->isChecked() ? FootstepConfig::Decimal : FootstepConfig::Degrees));
    _config->setMapTileCacheType((ui->_rdoDiskMemoryCache->isChecked() ? FootstepConfig::DiskMemoryCache : FootstepConfig::NoCache));
    _config->setMapTileExpiry(ui->_spnCacheExpiry->value());

    FootstepConfigLoader configLoader = FootstepConfigLoader();
    configLoader.saveConfiguration(_config);

    // Close the dialog window
    close();

}
