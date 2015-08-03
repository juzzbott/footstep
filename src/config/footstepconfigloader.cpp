#include <iostream>
#include <fstream>

#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringBuilder>
#include <QStandardPaths>
#include <QtDebug>

#include "footstepconfig.h"
#include "footstepconfigloader.h"
#include "core/constants.h"
#include "lib/json.h"

FootstepConfigLoader::FootstepConfigLoader()
{

    // Set the config location file path
    _configLocationFilePath = QCoreApplication::applicationDirPath() % "/.conf_loc";

    // Ensure a default configuration exists
    this->ensureDefaultConfiguration();

    // Load the configuration file
    //Json::Value root;
    //Json::Reader reader;
    //
    //QString configLocation = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QString(), QStandardPaths::LocateDirectory) % "/" % APP_SYS_NAME % "/config.json";
    //std::ifstream configStream(configLocation.toLatin1().data(), std::ifstream::binary);
    //bool result = reader.parse(configStream, root, false);
    //
    //if (result) {
    //    QString cache_dir(root.get("cache_dir", "").asCString());
    //    quint8 i = 0;
    //}

}

FootstepConfigLoader::~FootstepConfigLoader() {

    // Delete the config
    delete _config;

}

//
// Configuration location file
//

bool FootstepConfigLoader::confLocationFileExists() {

    // Esnures the configuration location file exists
    QFile fp(_configLocationFilePath);
    bool exists = fp.exists();

    // return the exits flag
    return exists;

}

void FootstepConfigLoader::saveConfLocationFile() {

    QFile fp(_configLocationFilePath);

    // Ensure the file can be opened for writing
    if (!fp.open(QIODevice::Truncate | QIODevice::WriteOnly)) {
        qWarning() << "Failed to open configuration location file for writing: " << fp.errorString();
        return;
    }

    QTextStream stream(&fp);
    stream << _configFilePath;
    qDebug() << "Config location file saved to: " << _configLocationFilePath;

}

void FootstepConfigLoader::loadConfigFilePath() {

    QFile fp(_configLocationFilePath);

    // Ensure the file can be opened for writing
    if (!fp.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open configuration location file for reading: " << fp.errorString();
        return;
    }

    QTextStream stream(&fp);
    stream >> _configFilePath;
}

void FootstepConfigLoader::ensureDefaultConfiguration() {

    // If the config file location does not exist, then generate the new config file path and save to the location file
    if (!this->confLocationFileExists()) {

        // Generate a default config file path
        _configFilePath = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QString(), QStandardPaths::LocateDirectory) % "/" % APP_SYS_NAME % "/config.json";
        // Save the location file
        this->saveConfLocationFile();

        FootstepConfig *defaultConfig = FootstepConfig::Default();

        quint8 i = 0;

    }

}

//
// Config
//

FootstepConfig *FootstepConfigLoader::config() const {
    return _config;
}
