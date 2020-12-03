#pragma once
#include <iostream>

#include <string>

using namespace std;
class L {
    public:
        string vertex_;
        int distance_;

        //constructor
        L();
        L(string v, int d);
    
        //update distance
        void update(int nd);
    
        //operators
        bool operator<(const L l) const;
        
};
