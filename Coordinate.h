#pragma once
#include <iostream>
#include <cmath>
class Coordinate {
    public:
        //The latitude of the place, positive for north and negative for south. Ranged from -90 to 90.
        double latitude;

        //The longitude of the place, positive for east and negative for west. Ranged from -180 to 80.
        double longitude;

        //constructors
        Coordinate();
        Coordinate(double lat, double lon);

        //calculates the difference in latitude from another coordinate, in degree
        double diff_lat_deg(const Coordinate & other);

        //calculates the difference in longitude from another coordinate, in degree
        double diff_lon_deg(const Coordinate & other);

        //calculates the difference in latitude from another coordinate, in radius
        double diff_lat_rad(const Coordinate & other);

        //calculates the difference in longitude from another coordinate, in radius
        double diff_lon_rad(const Coordinate & other);

        //calculates the closest distance between two coordinates
        double dis(const Coordinate & other);
        
};