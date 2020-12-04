#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "Airport.h"
#include "graph.h"
#include "L.h"
#include "heap.h"

using namespace std;

/*
 * Dijkstra function
 * This function will take a graph and two vertices as inputs
 * and return a map with the shortes flight route as the key and the shortest distance as value
 * If no route exists, the shortest distance will be -1
 */
map<vector<Vertex>, int> Dijkstra(Graph g, Vertex source, Vertex destination) {
    int dis_s_d = -1; // initial shortest distance from source to d
    map<vector<Vertex>, int> path; //a map with one key, the shortest path as a vector, and one value, the shortest distance
    map<Vertex, int> index; //a map with index as keys and all the vertices as values
    map<Vertex, int> L_m; //a map with all the vertices as keys and current shortest distance from source
    heap<L> L_h; //a heap with the vertices and its distance to source
    vector<vector<int>> w; //a matrix storing the distance for i to j
    map<Vertex, int> arrived; //a map that stores if a vertex has been found
    map<Vertex, vector<Vertex>> track; //a map containing the shortest the path from source to all vertices
    vector<Vertex> ap_id = g.getVertices(); //all vertices in the graph
    
    /*
     * Check if input is valid
     */
    int sum = 0;
    for (size_t i = 0; i < ap_id.size(); i++) {
        if (ap_id[i] == source || ap_id[i] == destination) {
            sum++;
        }
    }
    if (sum < 2) {
        cout << "Invalid Source or Destination" << endl;
        return path;
    } else {
        cout << "Valid Input" << endl;
    }
    
    /*
     * initiate path and track
     */
    vector<Vertex> path_;
    path_.push_back(source);
    for (size_t i = 0; i < ap_id.size(); i++) {
        track[ap_id[i]] = vector<Vertex>();
    }
    
    /*
     * build index
     * index of source is 0
     * index of destination is size - 1
     */
    for (size_t i = 0; i < ap_id.size(); i++) {
        index[ap_id[i]] = i;
    }
    
    /*
     * build L_m and L_h
     * distance from source to itself is 0
     * distance from all other vertices has initial value of -1
     */
    L_m[source] = 0;
    for (size_t i = 0; i < ap_id.size(); i++) {
        if (ap_id[i] != source) {
            L_m[ap_id[i]] = -1;
        }
    }
    L_h.push(L(source, 0));
    
    /*
     * build w
     * w[i][j] denotes the direct distance from i to j
     * w[i][j] = -1 if there is no flight from i to j
     */
    w.resize(ap_id.size());
    for (size_t i = 0; i < w.size(); i++) {
        w[i].resize(w.size(), -1);
    }
   for (size_t i = 0; i < ap_id.size(); i++) {
       Vertex tmp_v = ap_id[i];
       int from_ = index[tmp_v];
       vector<Vertex> tmp_vv = g.getAdjacent(tmp_v);
       for (size_t j = 0; j < tmp_vv.size(); j++) {
            int to_ = index[tmp_vv[j]];
            int wft = g.getEdgeWeight(tmp_v, tmp_vv[j]);
            w[from_][to_] = wft;
        }
        
    }
    
    /*
     * build arrived
     * -1 for not arrived
     * update to 0 when arrived
     */
    for (size_t i = 0; i < w.size(); i++) {
        arrived[ap_id[i]] = -1;
    }
    
    
    /*
     * Dijkstra Procedure
     */
    while (arrived[destination] == -1) {
        if (L_h.empty()) {
            //the case in which the destination is not connected to the source
            path[path_] = -1;
            break;
        }
        
        L tmp;
        Vertex u;
        int Lu;
        while (!L_h.empty()) {
            // return the vertex with the shortest distance
            tmp = L_h.pop();
            u = tmp.vertex_;
            Lu = tmp.distance_;
            // if not yet arrived
            if (arrived[u] != 0) {
                break;
            }
        }
        if (arrived[u] == 0) {
            //the case in which the destination is not connected to the source
            path[path_] = -1;
            break;
        }
        if (u == destination) {
            // destination arrived
            dis_s_d = Lu;
            track[destination].push_back(destination);
            break;
        }
        arrived[u] = 0; // mark u has arrived
        
        // check all the vertices not yet arrived
        for (auto it = arrived.begin(); it != arrived.end(); ++it) {
            if (it->second == 0) {
                continue;
            }
            Vertex v = it->first;
            int Lv = L_m[v];
            int wuv = w[index[u]][index[v]];
            if (Lv == -1) {
                // the case v has never been reached
                if (wuv != -1) {
                    // the case v is adjacent to u
                    Lv = Lu + wuv;
                    L_m[v] = Lv;
                    //push to heap and update track
                    L_h.push(L(v,Lv));
                    track[v] = track[u];
                    track[v].push_back(u);
                }
            } else {
                // the case v has been reached
                if (wuv != -1) {
                    // the case v is adjacent to u
                    if (Lu + wuv < Lv) {
                        Lv = Lu + wuv;
                        L_m[v] = Lv;
                        //update heap and update track
                        L_h.push(L(v,Lv));
                        track[v] = track[u];
                        track[v].push_back(u);
                    }
                }
            }
        }
    }
    if (path.size() == 0) {
        path[track[destination]] = dis_s_d;
    }
    
    return path;
    
    
    
}

