#include "footstepconfig.h"
#include "lib/json.h"

#include <QString>

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
