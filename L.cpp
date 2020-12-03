#include "L.h"
L::L() {
    vertex_ = "City not exists";
    distance_ = -1;
}
L::L(string v, int d) {
    vertex_ = v;
    distance_ = d;
}

void L::update(int nd) {
    distance_ = nd;
}

bool L::operator<(const L l) const {
    return distance_ < l.distance_;
}
