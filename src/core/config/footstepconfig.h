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
    enum MapTileCacheType { NoCache = 0, DiskMemoryCache = 1 };

public:
    FootstepConfig(const QString &profileDir);

    virtual void serialise(Json::Value &root);
    virtual void deserialise(Json::Value &root);

    bool profileDirChanged() const;

    QString profileDirectory() const;
    void setProfileDirectory(const QString &profileDirectory);

    QString originalProfileDirectory() const;

    CoordinateTypes coordinateType() const;
    void setCoordinateType(CoordinateTypes coordType);

    MapTileCacheType mapTileCacheType() const;
    void setMapTileCacheType(MapTileCacheType cacheType);

    short mapTileExpiry() const;
    void setMapTileExpiry(short mapTileExpiry);

    static FootstepConfig *Default();

private:

    bool _profileDirChanged;
    QString _originalProfileDir;

    QString _profileDirectory;
    CoordinateTypes _coordinateType;
    MapTileCacheType _mapTileCacheType;
    short _mapTileExpiry;

};

#endif // FOOTSTEPCONFIG_H
