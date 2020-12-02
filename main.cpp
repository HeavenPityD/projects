#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "route.h"
#include "Airport.h"
#include "graph.h"

using namespace std;

Airport findAirport(vector<Airport> airports, string ID) {
    for (int i = 0; i < (int)airports.size(); i++) {
        if (airports[i].ID == ID) {
            return airports[i];
        }
    }
    return Airport();
}
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
    vector<route> routes;

    while (std::getline(file, line)) {
        vector<string> v;
        if (line == "") {
            break;
        }
          //std::cout << line << std::endl;
        split(line, ',', v);
        v[1] = v[1].substr(1, v[1].length()-2);
        v[2] = v[2].substr(1, v[2].length() - 2);
        v[4] = v[4].substr(1, v[4].length() - 2);
        try{
            airports.push_back(Airport(v[1], v[2], std::stod(v[6]), std::stod(v[7]), v[4]));
        } catch (std::invalid_argument) {
            continue;
        }
    }
    file.close();
    
    file.open("routes.dat");
    while (std::getline(file, line)) {
        vector<string> v;
        if (line == "") {
            break;
        }
          //std::cout << line << std::endl;
        split(line, ',', v);
        Airport source = findAirport(airports, v[2]);
        Airport dest = findAirport(airports, v[4]);
        if (source == Airport() || dest == Airport()) {
            continue;
            std::cout << "Airport not found" << std::endl;
        }

        double dis = source.distance(dest);
        routes.push_back(route(source, dest, dis));
    }
    file.close();

    Graph g(true, true);
    for (size_t i = 0; i < airports.size(); i++) {
        g.insertVertex(airports[i].ID);
    }

    for (size_t i = 0; i < routes.size(); i++) {
        if (g.vertexExists(routes[i].source.ID) && g.vertexExists(routes[i].dest.ID)) {
            std::cout << "Edge created." << std::endl;
            g.insertEdge(routes[i].source.ID, routes[i].dest.ID);
            g.setEdgeWeight(routes[i].source.ID, routes[i].dest.ID, routes[i].weight);
        } else {
            std::cout << "Vertex not found" << std::endl;
        }
        
    }

    return 0;
}