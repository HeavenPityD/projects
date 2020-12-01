#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Airport.h"

using namespace std;

void split(const string & s, char c, vector<string> & v) {
    int i = 0;
    int j=s.find(c);
    if (s == "") return;
    
    while(j > 0 ) {
        v.push_back(s.substr(i, j-i));
        i = ++j;
        j = s.find(c, j);
    }
}

int main() {
    ifstream file;
    file.open("airports.dat");
    string line;
    vector<Airport> airports;

    while (std::getline(file, line)) {
        vector<string> v;
        if (line == "") {
            break;
        }
          //std::cout << line << std::endl;
        split(line, ',', v);
        v[1] = v[1].substr(1, v[1].length()-2);
        v[2] = v[2].substr(1, v[2].length() - 2);
        
        try{
            airports.push_back(Airport(v[1], v[2], std::stod(v[6]), std::stod(v[7])));
        } catch (std::invalid_argument) {
            continue;
        }
    }
    file.close();
    int i = 0;
    std::cout << airports.size() << std::endl;
    return 0;
}