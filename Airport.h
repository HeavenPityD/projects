#include "Coordinate.h"
class Airport {
    public:
        std::string name;
        std::string city;
        Coordinate cord;
        //constructors
        Airport();
        Airport(std::string name, std::string city, double lat, double lon);
        
        //returns the distance between two airports, in km.
        double distance(const Airport & other);
        

};