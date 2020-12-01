#include "Airport.h"
Airport::Airport() {

}

Airport::Airport(std::string n, std::string c, double lat, double lon, std::string id) {
    cord = Coordinate(lat, lon);
    name = n;
    city = c;
    ID = id;
}

double Airport::distance(const Airport & other) {
    return cord.dis(other.cord);
}