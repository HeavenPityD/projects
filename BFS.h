#pragma once

#include <iterator>
#include <queue>
#include <vector>
#include "graph.h"
#include <map>
using namespace std;

// BFS class to traverse from given node
class BFS {
    public: 
        BFS(Graph g, Vertex start);
        vector<Vertex> traverse();
    private:
        Graph g_;
        Vertex start_;
        bool allvisited_ = false;
        map<Vertex, bool> visited;
        vector<Vertex> vertices;
        void ifVisited();
    
    
};

