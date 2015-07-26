#ifndef MAPLAYER_H
#define MAPLAYER_H

#include <string>

#include <QObject>
#include <QWidget>
#include <QGridLayout>

#include "core/geopoint.h"

using namespace std;

class MapLayer : public QGridLayout
{
    Q_OBJECT

public:
    explicit MapLayer(QWidget *parent = 0);
    enum MapType { STREET, TOPOGRAPHIC };
    GeoPoint* getLocation();
    int getZoom();
    void setZoom(int zoom);

private:
    // Consts
    static const string OSM_MAP_URL_FORMAT;
    static const string CYCLE_MAP_URL_FORMAT;

    // Fields
    GeoPoint* loc;
    int zoom;

    // Methods
    int latToTileY(double lat, int zoom);
    int lonToTileX(double lon, int zoom);
    double tileXToLon(int x, int zoom);
    double tileYToLat(int y, int zoom);
    void loadMapImage(int x, int y, int zoom);

signals:

public slots:

};

#endif // MAPLAYER_H
