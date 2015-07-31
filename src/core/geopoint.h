#ifndef GEOPOINT
#define GEOPOINT

class GeoPoint {

public:
    GeoPoint();
    GeoPoint(double lat, double lon);
    GeoPoint(double lat, double lon, double alt);

    double latitude() const;
    double longitude() const;
    double altitude() const;

    void setPoint(double lat, double lon);
    void setPoint(double lat, double lon, double alt);

private:
    double _lat;
    double _lon;
    double _alt;

};

#endif // GEOPOINT

