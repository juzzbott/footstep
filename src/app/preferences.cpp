#include <QFileDialog>
#include <QLineEdit>
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
    FootstepConfig *config = configLoader.config();

    // Set the values of the controls on the form
    ui->_txtProfileDirectory->setText(config->profileDirectory());

    if (config->coordinateType() == FootstepConfig::Decimal) {
        ui->_rdoDecimal->setChecked(true);
    } else {
        ui->_rdoDegrees->setChecked(true);
    }

    if (config->mapTileCacheType() == FootstepConfig::DiskMemoryCache) {
        ui->_rdoDiskMemoryCache->setChecked(true);
    } else {
        ui->_rdoNoCache->setChecked(true);
    }

    ui->_spnCacheExpiry->setValue(config->mapTileExpiry());

}

Preferences::~Preferences()
{
    delete ui;
}

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
