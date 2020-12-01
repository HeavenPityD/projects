#include "Airport.h"
class route {
    public:
        Airport source;
        Airport dest;
        double weight;
        route();
        route(Airport s, Airport d, double w);
};