#include "footstepconfig.h"
#include "core/constants.h"
#include "lib/json.h"

#include <QString>
#include <QStringBuilder>
#include <QStandardPaths>

FootstepConfig::FootstepConfig()
{

}

FootstepConfig::FootstepConfig(Json::Value root) {

}

void FootstepConfig::setConfigValues(Json::Value root) {

}

//
// Profile Directory
//
QString FootstepConfig::profileDirectory() const {
    return _profileDirectory;
}

void FootstepConfig::setProfileDirectory(QString &profileDirectory) {
    _profileDirectory = profileDirectory;
}

//
// Coordinate type
//
FootstepConfig::CoordinateTypes FootstepConfig::coordinateType() const {
    return _coordinateType;
}

void FootstepConfig::setCoordinateType(CoordinateTypes coordType) {
    _coordinateType = coordType;

}

//
// Default configuration
//
FootstepConfig *FootstepConfig::Default() {

    FootstepConfig *config = new FootstepConfig();

    // Set the default profile dir.
    QString profileDir = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QString(), QStandardPaths::LocateDirectory) % "/" % APP_SYS_NAME;
    config->setProfileDirectory(profileDir);

    // Set the default coordinate type
    config->setCoordinateType(FootstepConfig::Decimal);

    // return the configuration
    return config;

}
