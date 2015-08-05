#ifndef FOOTSTEPCONFIG_H
#define FOOTSTEPCONFIG_H

#include <QString>

#include <string>

#include "core/json/json.h"
#include "core/json/ijsonserializable.h"

class FootstepConfig : public IJsonSerializable
{

public:
    enum CoordinateTypes { Decimal = 1, Degrees };
    enum MapTileCacheType { None = 0, DiskMemoryCache = 1 };

public:
    FootstepConfig();

    virtual void serialise(Json::Value &root);
    virtual void deserialise(Json::Value &root);

    QString profileDirectory() const;
    void setProfileDirectory(QString &profileDirectory);

    CoordinateTypes coordinateType() const;
    void setCoordinateType(CoordinateTypes coordType);

    MapTileCacheType mapTileCacheType() const;
    void setMapTileCacheType(MapTileCacheType cacheType);

    short mapTileExpiry() const;
    void setMapTileExpiry(short mapTileExpiry);

    static FootstepConfig *Default();

private:

    /**
     * @brief Sets the configuration values from the Json::Value root objet.
     * @param root
     */
    void setConfigValues(Json::Value root);

    QString _profileDirectory;
    CoordinateTypes _coordinateType;
    MapTileCacheType _mapTileCacheType;
    short _mapTileExpiry;

};

#endif // FOOTSTEPCONFIG_H
