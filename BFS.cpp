#include <queue>
#include "BFS.h"
#include "graph.h"
#include <map>

using std::queue;

BFS::BFS(Graph g, Vertex start) {
    g_ = g;
    start_ = start;
    vertices.push_back(start_);
}

void BFS::ifVisited() {
    for (auto it = visited.begin(); it !=visited.end(); it++) {
        if (it->second == false) allvisited_ = false;
    }
    allvisited_ = true;
}

bool ifExist(vector<Vertex> a, Vertex b) {
    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] == b) return true;
    }
    return false;
}

vector<Vertex> BFS::traverse() {
    
    vector<Vertex> all = g_.getVertices();
    for (size_t i = 0; i < all.size(); i++) {
        visited[all[i]] = false;
    }

    int pos = 0;
    while (!allvisited_) {
        if (pos >= (int) vertices.size()) break;
        vector<Vertex> adj = g_.getAdjacent(vertices[pos]);
        for (size_t j = 0; j < adj.size(); j++) {
            if(!ifExist(vertices, adj[j])) {
                vertices.push_back(adj[j]);
            }
        }
        pos++;
    }
    return vertices;
    
}

