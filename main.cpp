#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "route.h"
#include "Airport.h"
#include "graph.h"
#include "dijkstra.cpp"

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
            if (v[4] == "") continue;
            airports.push_back(Airport(v[1], v[2], std::stod(v[6]), std::stod(v[7]), v[4]));
        } catch (std::invalid_argument) {
            continue;
        }
    }
    file.close();
    
    Graph g(true, true);
    for (size_t i = 0; i < airports.size(); i++) {
        g.insertVertex(airports[i].ID);
    }

    ifstream dis_file;
    dis_file.open("distance.csv");
    while(std::getline(dis_file, line)) {
        vector<string> v;
        if (line == "") {
            break;
        }
        split(line, ',', v);
        g.insertEdge(v[0], v[1]);
        g.setEdgeWeight(v[0], v[1], std::stod(v[2]));
    }
    
    dis_file.close();
    
    
    
    
    
    
    cout << "start" << endl;
    Vertex source_ = "JFK";
    Vertex destination_ = "ORD";
    
    map<vector<Vertex>, int> d_path_n_distance = Dijkstra(g, source_, destination_);
    
    vector<Vertex> d_path = d_path_n_distance.begin()->first;
    vector<Airport> air_path; // Air_path stores airports of the path
    for (size_t i = 0; i < d_path.size(); i++) {
        air_path.push_back(findAirport(airports, d_path[i]));
    }
    
    int d_distance = d_path_n_distance.begin()->second;
    if (d_distance == -1) {
        cout << "No fligh available from " << source_ << " to " << destination_ << endl;
    } else {
        cout << "Shortest flight route from " << source_ << " to " << destination_ << " is: ";
        for (size_t i = 0; i < d_path.size(); i++) {
            cout << d_path[i] << " ";
        }
        cout << endl;
        cout << "The corresponding shortest distance is " << d_distance << endl;
    }
    
    vector<Vertex> source_a = g.getAdjacent(source_);
    bool direct_flight = false;
    for (size_t i = 0; i < source_a.size(); i++) {
        if (source_a[i] == destination_) {
            direct_flight = true;
        }
    }
    if (direct_flight) {
        cout << "The direct distance between " << source_ << " and " << destination_ << " is " << g.getEdgeWeight(source_, destination_) << endl;
    } else {
        cout << "No direct flight from " << source_ << " to " << destination_ << endl;
    }

    /*
    cout << "debugging" << endl;
    vector<Vertex> FNJ_A = g.getAdjacent("FNJ");
    for (size_t i = 0; i < FNJ_A.size(); i++) {
        cout << FNJ_A[i] << ": ";
        cout << g.getEdgeWeight("FNJ", FNJ_A[i]) << endl;
    }
     */



    /*
    //For Dijkstra testing
    Graph testing_graph(true, true);
    for (int i = 0; i <= 14; i++) {
        testing_graph.insertVertex(std::to_string(i));
    }
    testing_graph.insertEdge("1", "2");
    testing_graph.setEdgeWeight("1", "2", 6);
    testing_graph.insertEdge("2", "1");
    testing_graph.setEdgeWeight("2", "1", 6);
    testing_graph.insertEdge("1", "14");
    testing_graph.setEdgeWeight("1", "14", 19);
    testing_graph.insertEdge("3", "2");
    testing_graph.setEdgeWeight("3", "2", 7);
    testing_graph.insertEdge("3", "11");
    testing_graph.setEdgeWeight("3", "11", 4);
    testing_graph.insertEdge("11", "3");
    testing_graph.setEdgeWeight("11", "3", 4);
    testing_graph.insertEdge("1", "4");
    testing_graph.setEdgeWeight("1", "4", 1);
    testing_graph.insertEdge("4", "1");
    testing_graph.setEdgeWeight("4", "1", 1);
    testing_graph.insertEdge("4", "11");
    testing_graph.setEdgeWeight("4", "11", 10);
    testing_graph.insertEdge("11", "4");
    testing_graph.setEdgeWeight("11", "4", 10);
    testing_graph.insertEdge("4", "5");
    testing_graph.setEdgeWeight("4", "5", 2);
    testing_graph.insertEdge("4", "10");
    testing_graph.setEdgeWeight("4", "10", 8);
    testing_graph.insertEdge("10", "4");
    testing_graph.setEdgeWeight("10", "4", 8);
    testing_graph.insertEdge("6", "5");
    testing_graph.setEdgeWeight("6", "5", 4);
    testing_graph.insertEdge("6", "10");
    testing_graph.setEdgeWeight("6", "10", 1);
    testing_graph.insertEdge("10", "6");
    testing_graph.setEdgeWeight("10", "6", 1);
    testing_graph.insertEdge("5", "7");
    testing_graph.setEdgeWeight("5", "7", 3);
    testing_graph.insertEdge("7", "5");
    testing_graph.setEdgeWeight("7", "5", 3);
    testing_graph.insertEdge("7", "14");
    testing_graph.setEdgeWeight("7", "14", 4);
    testing_graph.insertEdge("14", "7");
    testing_graph.setEdgeWeight("14", "7", 4);
    testing_graph.insertEdge("7", "8");
    testing_graph.setEdgeWeight("7", "8",6);
    testing_graph.insertEdge("8", "9");
    testing_graph.setEdgeWeight("8", "9", 2);
    testing_graph.insertEdge("9", "8");
    testing_graph.setEdgeWeight("9", "8", 2);
    testing_graph.insertEdge("7", "12");
    testing_graph.setEdgeWeight("7", "12", 7);
    testing_graph.insertEdge("12", "7");
    testing_graph.setEdgeWeight("12", "7", 7);
    
    cout << "start" << endl;
    Vertex source_ = "1";
    Vertex destination_ = "14";
    
    map<vector<Vertex>, int> d_path_n_distance = Dijkstra(testing_graph, source_, destination_);
    
    vector<Vertex> d_path = d_path_n_distance.begin()->first;
    int d_distance = d_path_n_distance.begin()->second;
    if (d_distance == -1) {
        cout << "No fligh available from " << source_ << " to " << destination_ << endl;
    } else {
        cout << "Shortest flight route from " << source_ << " to " << destination_ << " is: ";
        for (size_t i = 0; i < d_path.size(); i++) {
            cout << d_path[i] << " ";
        }
        cout << endl;
        cout << "The corresponding shortest distance is " << d_distance << endl;
    }
    
    
    cout << "The direct distance between " << source_ << " and " << destination_ << " is " << testing_graph.getEdgeWeight(source_, destination_) << endl;
    
    */
    
    
    return 0;
}
