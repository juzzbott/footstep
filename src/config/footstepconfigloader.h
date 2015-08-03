#ifndef FOOTSTEPCONFIGLOADER_H
#define FOOTSTEPCONFIGLOADER_H

#include "footstepconfig.h"

#include <QString>

class FootstepConfigLoader
{
public:
    FootstepConfigLoader();
    ~FootstepConfigLoader();

    FootstepConfig *config() const;

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
     * @brief Ensures that the application always has a default configuration.
     */
    void ensureDefaultConfiguration();

    QString _configLocationFilePath;
    QString _configFilePath;

    FootstepConfig *_config;


};

#endif // FOOTSTEPCONFIGLOADER_H
