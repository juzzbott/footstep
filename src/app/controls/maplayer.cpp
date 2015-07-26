#include "math.h"
#include "string.h"

#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include <QString>

#include "maplayer.h"
#include "core/geopoint.h"

using namespace std;

// Constants
const string OSM_MAP_URL_FORMAT = "http://a.tile.openstreetmap.org/%d/%d/%d.png";
const string CYCLE_MAP_URL_FORMAT = "http://a.tile.opencyclemap.org/cycle/%d/%d/%d.png";

MapLayer::MapLayer(QWidget *parent) : QGridLayout(parent)
{
    this->loc = new GeoPoint(0.0, 0.0 ,0.0);
    this->zoom = 0;

    // Create the grid layout
    this->setHorizontalSpacing(0);
    this->setVerticalSpacing(0);

    QLabel *myimage = new QLabel();
    myimage->setText("Hello");

    //QPixmap pix("E:\\Development\\map_tiles\\1.png");
    //myimage->setPixmap(pix);

    this->addWidget(myimage, 0, 0);
}

GeoPoint *MapLayer::getLocation() {
    return this->loc;
}

int MapLayer::getZoom() {
    return this->zoom;
}

void MapLayer::setZoom(int zoom) {
    this->zoom = zoom;
}

int MapLayer::latToTileY(double lat, int zoom) {
    return (int)(floor((1.0 - log(tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, zoom)));
}

int MapLayer::lonToTileX(double lon, int zoom) {
    return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, zoom)));
}

double MapLayer::tileXToLon(int x, int zoom) {
    return x / pow(2.0, zoom) * 360.0 - 180;
}

double MapLayer::tileYToLat(int y, int zoom) {
    double n = M_PI - 2.0 * M_PI * y / pow(2.0, zoom);
    return 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
}

void MapLayer::loadMapImage(int x, int y, int zoom) {



}
