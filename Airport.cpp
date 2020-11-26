#include "Airport.h"
Airport::Airport() {

}

Airport::Airport(std::string n, std::string c, double lat, double lon) {
    cord = Coordinate(lat, lon);
    name = n;
    city = c;
}

double Airport::distance(const Airport & other) {
    return cord.dis(other.cord);
}