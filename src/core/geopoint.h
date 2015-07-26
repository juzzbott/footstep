#ifndef GEOPOINT
#define GEOPOINT

class GeoPoint {

public:
    GeoPoint(double lat, double lon);
    GeoPoint(double lat, double lon, double alt);

    double getLatitude();
    double getLongitude();
    double getAltitude();

    void setPoint(double lat, double lon);
    void setPoint(double lat, double lon, double alt);

private:
    double lat;
    double lon;
    double alt;

};

#endif // GEOPOINT

