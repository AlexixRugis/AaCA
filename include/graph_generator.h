#pragma once

#include <unordered_set>
#include <random>
#include <stdexcept>
#include "graph.h"

struct EdgeHash {
    std::size_t operator () (const Graph::Edge &p) const {
        auto h1 = std::hash<size_t>{}(p.first);
        auto h2 = std::hash<size_t>{}(p.second);
        return h1 ^ h2;
    }
};

Graph generateGraph(size_t verticesCount, size_t edgesCount) {
    
    if (verticesCount == 0) {
        throw std::invalid_argument("verticesCount must be positive");
    }

    if (edgesCount > verticesCount * (verticesCount - 1) / 2) {
        throw std::invalid_argument("edgesCount must be between 0 and n*(n - 1)/2 where n=verticesCount");
    }

    Graph res(verticesCount);

    std::unordered_set<Graph::Edge, EdgeHash> edges;

    std::random_device rd;
    std::uniform_int_distribution<size_t> uniform(0, verticesCount - 1);
    
    for (size_t i = 0; i < edgesCount; i++) {
        bool added = false;

        while (!added) {
        size_t x = uniform(rd);
        size_t y = uniform(rd);

        if (x == y) {
            continue;
        }
        if (x > y) {
            std::swap(x, y);
        }

        Graph::Edge newEdge = Graph::Edge{x, y};

        if (edges.count(newEdge)) {
            continue;
        }

        edges.insert(newEdge);
        res.addEdge(x, y);
        added = true;
    }

    return res;
}