#include "Airport.h"

Airport::Airport() {

}

Airport::Airport(std::string n, std::string c, double lat, double lon, std::string id) {
    cord = Coordinate(lat, lon);
    name = n;
    city = c;
    ID = id;
    latitude = lat;
    longitude = lon;
}

double Airport::distance(const Airport & other) {
    return cord.dis(other.cord);
}

bool Airport::operator== (Airport a) {
    if (name == a.name && ID == a.ID) {
        return true;
    } 
    return false;
}