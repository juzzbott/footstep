#ifndef FOOTSTEPCONFIGLOADER_H
#define FOOTSTEPCONFIGLOADER_H

#include "footstepconfig.h"
#include "core/json/ijsonserializable.h"

#include <QString>

class FootstepConfigLoader
{
public:
    FootstepConfigLoader();
    ~FootstepConfigLoader();

    /**
     * @brief Returns the configuration object.
     * @return
     */
    FootstepConfig *config() const;

    /**
     * @brief Writes the configuration file to the disk.
     */
    void writeConfigurationFile(IJsonSerializable *config);

private:
    /**
     * @brief Determines if the config location file exists or not. Used to determine if a base configuration exists
     */
    bool confLocationFileExists();

    /**
     * @brief Saves the configuration location file which specifies the filepath to the configuration file.
     * @param configFileLocation The file path of the configuration file.
     */
    void saveConfLocationFile();

    /**
     * @brief Loads the configuration file path into the _configFilePath variable.
     */
    void loadConfigFilePath();

    /**
     * @brief Determines if the configuration file exists.
     */
    bool configFileExists();

    /**
     * @brief Ensures that the application always has a default configuration.
     */
    void ensureDefaultConfiguration();

    /**
     * @brief Reads the configuration file from disk and make's it available from the config() getter.
     * @return
     */
    void readConfigurationFile();

    QString _configLocationFilePath;
    QString _configFilePath;

    FootstepConfig *_config;


};

#endif // FOOTSTEPCONFIGLOADER_H
