#include <QString>
#include <QStringBuilder>
#include <QStandardPaths>

#include <string>

#include "footstepconfig.h"
#include "constants.h"
#include "json/json.h"

FootstepConfig::FootstepConfig(const QString &profileDir)
{
    _profileDirectory = profileDir;
    _originalProfileDir = profileDir;
    _profileDirChanged = false;
}

//
// Profile Directory
//
QString FootstepConfig::profileDirectory() const {
    return _profileDirectory;
}

void FootstepConfig::setProfileDirectory(const QString &profileDir) {

    if (profileDir != _profileDirectory) {

        _profileDirectory = profileDir;
        _profileDirChanged = true;

    }
}

bool FootstepConfig::profileDirChanged() const {
    return _profileDirChanged;
}

QString FootstepConfig::originalProfileDirectory() const {
    return _originalProfileDir;
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
// Map Tile Cache Type
//
FootstepConfig::MapTileCacheType FootstepConfig::mapTileCacheType() const {
    return _mapTileCacheType;
}

void FootstepConfig::setMapTileCacheType(MapTileCacheType cacheType) {
    _mapTileCacheType = cacheType;
}

//
// Map tile expiry
//
short FootstepConfig::mapTileExpiry() const {
    return _mapTileExpiry;
}

void FootstepConfig::setMapTileExpiry(short mapTileExpiry) {
    _mapTileExpiry = mapTileExpiry;
}

//
// Default configuration
//
FootstepConfig *FootstepConfig::Default() {

    // Set the default profile dir.
    QString profileDir = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QString(), QStandardPaths::LocateDirectory) % APP_SYS_NAME;

    // Create the config at the profile dir
    FootstepConfig *config = new FootstepConfig(profileDir);

    // Set the default coordinate type
    config->setCoordinateType(FootstepConfig::Decimal);

    // Set the default map tile cache type
    config->setMapTileCacheType(FootstepConfig::DiskMemoryCache);

    // Set the default map tile expiry
    config->setMapTileExpiry(14);

    // return the configuration
    return config;

}

//
// IJsonSerializable
//
void FootstepConfig::serialise(Json::Value &root) {

    root["coord_type"] = _coordinateType;
    root["map_tile_cache_type"] = _mapTileCacheType;
    root["map_tile_expiry"] = _mapTileExpiry;

}

void FootstepConfig::deserialise(Json::Value &root) {

    _coordinateType = (CoordinateTypes)root.get("coord_type", 1).asInt();
    _mapTileCacheType = (MapTileCacheType)root.get("map_tile_cache_type", 1).asInt();
    _mapTileExpiry = (short)root.get("map_tile_expiry", 14).asInt();

}
