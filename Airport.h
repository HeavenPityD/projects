#include "Coordinate.h"
#pragma once
class Airport {
    public:
        std::string name;
        std::string city;
        Coordinate cord;
        std::string ID;
        //constructors
        Airport();
        Airport(std::string name, std::string city, double lat, double lon, std::string id);
        
        //returns the distance between two airports, in km.
        double distance(const Airport & other);
        
        bool operator== (Airport a);
};