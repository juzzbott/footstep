#include "geopoint.h"

GeoPoint::GeoPoint() {
    this->setPoint(0, 0);
}

GeoPoint::GeoPoint(double lat, double lon) {
    this->setPoint(lat, lon);
}

GeoPoint::GeoPoint(double lat, double lon, double alt) {
    this->setPoint(lat, lon, alt);
}

double GeoPoint::altitude() const {
    return this->_alt;
}

double GeoPoint::latitude() const {
    return this->_lat;
}

double GeoPoint::longitude() const {
    return this->_lon;
}

void GeoPoint::setPoint(double lat, double lon) {
    this->_lat = lat;
    this->_lon = lon;
    this->_alt = 0;
}

void GeoPoint::setPoint(double lat, double lon, double alt) {
    this->_lat = lat;
    this->_lon = lon;
    this->_alt = alt;
}
