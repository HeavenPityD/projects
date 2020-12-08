#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "route.h"
#include "Airport.h"
#include "graph.h"
#include "dijkstra.cpp"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

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

int transe_latitude(double latitude, cs225::PNG const png)
{
    // transe latitude to [0,180]
    if(latitude< -90 )
    {
        latitude = -90;
    }
    if(latitude >90)
    {
        latitude = 90;
    }
    double new_lat = latitude + 90;
    //cout << "height = " << png.height() << endl;
    return png.height() - new_lat / 180.0 * png.height();
}

int transe_longitude(double longitude,cs225::PNG const png)
{
    // transe longitude to [0,360]
    if(longitude< -180 )
    {
        longitude = -180;
    }
    if(longitude >180)
    {
        longitude = 180;
    }
    double new_lon = longitude + 180;
    //cout << "width = " << png.width() << endl;
    return new_lon / 360.0 * png.width();
}

void sDColor (cs225::HSLAPixel& pixel) {
    pixel.h = 0;
    pixel.s = 0.9;
    pixel.l = 0.6;
}

void drawSD(double lat, double lon, cs225::PNG& png) {
    int new_lat1 =transe_latitude(lat, png);
    int new_lon1 = transe_longitude(lon, png);
    for (int x = new_lon1; x >= new_lon1 - 4; x--) {
        for (int y = new_lat1; y >= new_lat1 - 4; y--) {
            cs225::HSLAPixel& pixel = png.getPixel(x, y);
            sDColor(pixel);
        }
    }
    for (int x = new_lon1; x >= new_lon1 - 4; x--) {
        for (int y = new_lat1; y <= new_lat1 + 4; y++) {
            cs225::HSLAPixel& pixel = png.getPixel(x, y);
            sDColor(pixel);
        }
    }
    for (int x = new_lon1; x <= new_lon1 + 4; x++) {
        for (int y = new_lat1; y <= new_lat1 + 4; y++) {
            cs225::HSLAPixel& pixel = png.getPixel(x, y);
            sDColor(pixel);
        }
    }
    for (int x = new_lon1; x <= new_lon1 + 4; x++) {
        for (int y = new_lat1; y >= new_lat1 - 4; y--) {
            cs225::HSLAPixel& pixel = png.getPixel(x, y);
            sDColor(pixel);
        }
    }
}

void airportColor (cs225::HSLAPixel& pixel) {
    pixel.h = 135;
    pixel.s = 0.9;
    pixel.l = 0.6;
}

void drawAirport(double lat, double lon, cs225::PNG& png) {
    int new_lat1 =transe_latitude(lat, png);
    int new_lon1 = transe_longitude(lon, png);
    for (int x = new_lon1; x >= new_lon1 - 3; x--) {
        for (int y = new_lat1; y >= new_lat1 - 3; y--) {
            cs225::HSLAPixel& pixel = png.getPixel(x, y);
            airportColor(pixel);
        }
    }
    for (int x = new_lon1; x >= new_lon1 - 3; x--) {
        for (int y = new_lat1; y <= new_lat1 + 3; y++) {
            cs225::HSLAPixel& pixel = png.getPixel(x, y);
            airportColor(pixel);
        }
    }
    for (int x = new_lon1; x <= new_lon1 + 3; x++) {
        for (int y = new_lat1; y <= new_lat1 + 3; y++) {
            cs225::HSLAPixel& pixel = png.getPixel(x, y);
            airportColor(pixel);
        }
    }
    for (int x = new_lon1; x <= new_lon1 + 3; x++) {
        for (int y = new_lat1; y >= new_lat1 - 3; y--) {
            cs225::HSLAPixel& pixel = png.getPixel(x, y);
            airportColor(pixel);
        }
    }
}

void routeColor (cs225::HSLAPixel& pixel) {
    pixel.h = 45;
    pixel.s = 0.9;
    pixel.l = 0.6;
}

void drawLine(double lat1,double lon1,double lat2 , double lon2 , cs225::PNG& png)
{
    // get transed address
    int new_lat1 =transe_latitude(lat1, png);
    int new_lon1 = transe_longitude(lon1, png);
    int new_lat2 = transe_latitude(lat2, png);
    int new_lon2 = transe_longitude(lon2, png);
    //cout <<new_lat1 << endl;
    //cout <<new_lon1 << endl;
    //cout <<new_lat2 << endl;
    //cout <<new_lon2 << endl;
    
    int maxLat = new_lat1 > new_lat2 ? new_lat1 : new_lat2;
    int minLat = new_lat1 < new_lat2 ? new_lat1 : new_lat2;
    int start_x = new_lat1 < new_lat2 ? new_lon1 : new_lon2;
    int maxLon = new_lon1 > new_lon2 ? new_lon1 : new_lon2;
    int minLon = new_lon1 < new_lon2 ? new_lon1 : new_lon2;
    int start_y = new_lon1 < new_lon2 ? new_lat1 : new_lat2;
    // calc slope
    // deal with minLat  == maxLat
    double value = (maxLat - minLat) / (maxLon - minLon);
    if(minLat == maxLat)
    {
        int y = minLat;
        for(int x = minLon ; x <= maxLon ; x ++) {
            for (int i = 0; i < 2; i++) {
                cs225::HSLAPixel& pixel = png.getPixel(x - i, y);
                routeColor(pixel);
            }
            for (int i = 0; i < 2; i++) {
                cs225::HSLAPixel& pixel = png.getPixel(x + i, y);
                routeColor(pixel);
            }
        }
    }
    else if (value < 1)
    {
        double k = ((double)(new_lat1 - new_lat2)) / (new_lon1 - new_lon2);
        for(int x = minLon ; x <= maxLon ; x ++)
        {
            int y = k * (x - minLon) + start_y;
            //cout << y << "\t" << x << endl;
            for (int i = 0; i < 2; i++) {
                cs225::HSLAPixel& pixel = png.getPixel(x, y - i);
                routeColor(pixel);
            }
            for (int i = 0; i < 2; i++) {
                cs225::HSLAPixel& pixel = png.getPixel(x, y + i);
                routeColor(pixel);
            }
        }
    }
    else
    {
        double k = ((double)(new_lon1 - new_lon2)) / (new_lat1 - new_lat2);
        for(int y = minLat ; y <= maxLat ; y ++)
        {
            int x = k * (y - minLat) + start_x;
            //cout << y << "\t" << x << endl;
            for (int i = 0; i < 2; i++) {
                cs225::HSLAPixel& pixel = png.getPixel(x - i, y);
                routeColor(pixel);
            }
            for (int i = 0; i < 2; i++) {
                cs225::HSLAPixel& pixel = png.getPixel(x + i, y);
                routeColor(pixel);
            }
        }
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
    Vertex source_ = "SIN";
    Vertex destination_ = "JFK";
    
    map<vector<Vertex>, int> d_path_n_distance = Dijkstra(g, source_, destination_);
    
    vector<Vertex> d_path = d_path_n_distance.begin()->first;
    vector<Airport> air_path;
    for (size_t i = 0; i < d_path.size(); i++) {
        air_path.push_back(findAirport(airports, d_path[i]));
    }
    // draw pic
    // open picture
    string image = "Blankmap.png";
    cs225::PNG png;
    png.readFromFile(image);
    for (size_t i = 0; i < air_path.size(); i++) {
        double lat = air_path[i].latitude;
        double lon = air_path[i].longitude;
        drawAirport(lat, lon, png);
    }
    for (size_t i = 0; i < air_path.size(); i++) {
        double lat1 = air_path[0].latitude;
        double lon1 = air_path[0].longitude;
        drawSD(lat1, lon1, png);
        double lat2 = air_path[air_path.size() - 1].latitude;
        double lon2 = air_path[air_path.size() - 1].longitude;
        drawSD(lat2, lon2, png);
    }
    for (size_t i = 0; i < air_path.size()-1; i++) {
        // get latitude and longitude 
        double lat1 = air_path[i].latitude;
        double lon1 = air_path[i].longitude;
        double lat2 = air_path[i+1].latitude;
        double lon2 = air_path[i+1].longitude;
        drawLine(lat1,lon1,lat2 ,lon2 ,png);
    }
    
    // write result into picture
    png.writeToFile("Result.png");
    int d_distance = d_path_n_distance.begin()->second;
    if (d_distance == -1) {
        cout << "No flight available from " << source_ << " to " << destination_ << endl;
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
