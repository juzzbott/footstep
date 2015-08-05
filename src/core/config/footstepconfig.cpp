#include <QString>
#include <QStringBuilder>
#include <QStandardPaths>

#include <string>

#include "footstepconfig.h"
#include "constants.h"
#include "json/json.h"

FootstepConfig::FootstepConfig()
{

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

    FootstepConfig *config = new FootstepConfig();

    // Set the default profile dir.
    QString profileDir = QStandardPaths::locate(QStandardPaths::GenericDataLocation, QString(), QStandardPaths::LocateDirectory) % APP_SYS_NAME;
    config->setProfileDirectory(profileDir);

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

    root["profile_dir"] = _profileDirectory.toStdString();
    root["coord_type"] = _coordinateType;
    root["map_tile_cache_type"] = _mapTileCacheType;
    root["map_tile_expiry"] = _mapTileExpiry;

}

void FootstepConfig::deserialise(Json::Value &root) {

    std::string str = root.get("profile_dir", "").asString();

    _profileDirectory = QString::fromUtf8(str.c_str());
    _coordinateType = (CoordinateTypes)root.get("coord_type", 1).asInt();
    _mapTileCacheType = (MapTileCacheType)root.get("map_tile_cache_type", 1).asInt();
    _mapTileExpiry = (short)root.get("map_tile_expiry", 14).asInt();

}
