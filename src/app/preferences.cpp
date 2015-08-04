#include <QFileDialog>
#include <QLineEdit>
#include <QStandardPaths>

#include "preferences.h"
#include "ui_preferences.h"
#include "core/config/footstepconfigloader.h"

Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);

    // Set the default path
    QString configLocation = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QString(), QStandardPaths::LocateDirectory);
    ui->_txtProfileDirectory->setText(configLocation);

    FootstepConfigLoader config = FootstepConfigLoader();

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
