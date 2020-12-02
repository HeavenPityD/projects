
#include "Coordinate.h"
Coordinate::Coordinate() {}

Coordinate::Coordinate(double lat, double lon) {
    latitude = lat;
    longitude = lon;
}

double Coordinate::diff_lat_deg(const Coordinate & other) {
    return abs(latitude - other.latitude);
}

double Coordinate::diff_lon_deg(const Coordinate & other) {
    return std::min(abs(longitude - other.longitude), 360 - abs(longitude - other.longitude));
}

double Coordinate::diff_lat_rad(const Coordinate & other) {
    return diff_lat_deg(other) * 3.1415926 / 180;
}

double Coordinate::diff_lon_rad(const Coordinate & other) {
    return diff_lon_deg(other) * 3.1415926 / 180;
}

double Coordinate::dis(const Coordinate & other) {
    double R = 6371;
    double dLat = diff_lat_rad(other);
    double dLon = diff_lon_rad(other);
    double a = sin(dLat/2) * sin(dLat/2) + cos(latitude * 3.1415926 / 180) * cos(other.latitude * 3.1415926 / 180) * sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return R * c;
}