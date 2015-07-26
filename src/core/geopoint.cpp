#include "geopoint.h"

GeoPoint::GeoPoint(double lat, double lon) {
    this->lat = lat;
    this->lon = lon;
}

GeoPoint::GeoPoint(double lat, double lon, double alt) {
    this->lat = lat;
    this->lon = lon;
    this->alt = alt;
}

double GeoPoint::getAltitude() {
    return this->alt;
}

double GeoPoint::getLatitude() {
    return this->lat;
}

double GeoPoint::getLongitude() {
    return this->lon;
}

void GeoPoint::setPoint(double lat, double lon) {
    this->lat = lat;
    this->lon = lon;
}

void GeoPoint::setPoint(double lat, double lon, double alt) {
    this->lat = lat;
    this->lon = lon;
    this->alt = alt;
}
