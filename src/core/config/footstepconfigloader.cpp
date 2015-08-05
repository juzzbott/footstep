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
#include "constants.h"
#include "json/json.h"
#include "json/ijsonserializable.h"

FootstepConfigLoader::FootstepConfigLoader()
{

    // Set the config location file path
    _configLocationFilePath = QCoreApplication::applicationDirPath() % "/.conf_loc";

    // Ensure a default configuration exists
    this->ensureDefaultConfiguration();

    // read the configuration
    this->readConfigurationFile();

}

FootstepConfigLoader::~FootstepConfigLoader() {

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

    } else {

        // Load the configuration file location
        this->loadConfigFilePath();

    }

    // If there is no configuration file, then create a default one
    if (!this->configFileExists()) {

        // Write the configuration
        FootstepConfig *defaultConfig = FootstepConfig::Default();
        this->writeConfigurationFile(defaultConfig);

    }

}

//
// Read/Write configuration file
//

bool FootstepConfigLoader::configFileExists() {

    // Esnures the configuration location file exists
    QFile fp(_configFilePath);
    bool exists = fp.exists();

    // return the exits flag
    return exists;

}

void FootstepConfigLoader::writeConfigurationFile(IJsonSerializable *config) {

    // Ensure the config item is not null
    if (config == NULL) {
        return;
    }

    // Serialise the json data
    Json::Value root;
    config->serialise(root);

    // Write the json file to the stream.
    Json::StyledStreamWriter writer;
    std::ofstream fsOut(_configFilePath.toStdString().c_str());
    writer.write(fsOut, root);
    fsOut.close();

}

void FootstepConfigLoader::readConfigurationFile() {

    // Read the json data from the file.
    Json::Value root;
    Json::Reader reader;
    std::ifstream fsIn(_configFilePath.toStdString().c_str());
    bool result = reader.parse(fsIn, root);

    // If the result was successfull, then deserialise the json data to a FootStep config object
    if (result) {

        FootstepConfig *config = new FootstepConfig();
        config->deserialise(root);

        _config = config;

    }


}

//
// Config
//

FootstepConfig *FootstepConfigLoader::config() const {
    return _config;
}
