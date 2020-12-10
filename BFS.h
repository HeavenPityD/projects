#pragma once

#include <iterator>
#include <queue>
#include <vector>
#include "graph.h"
#include <map>
using namespace std;

class BFS {
    public: 
        BFS(Graph g, Vertex start);
        vector<Vertex> traverse();
        void ifVisited();
    private:
        Graph g_;
        Vertex start_;
        bool allvisited_ = false;
        map<Vertex, bool> visited;
        vector<Vertex> vertices;
};

