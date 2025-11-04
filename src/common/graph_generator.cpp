#include "graph_generator.h"

#include <random>
#include <stdexcept>

Graph generateGraph(size_t verticesCount, size_t edgesCount)
{
    if (verticesCount == 0)
    {
        throw std::invalid_argument("verticesCount must be positive");
    }

    if (edgesCount > verticesCount * (verticesCount - 1) / 2)
    {
        throw std::invalid_argument("edgesCount must be between 0 and n*(n - 1)/2 where n=verticesCount");
    }

    Graph res(verticesCount);

    std::vector<Graph::Edge> edges;
    edges.reserve(verticesCount * (verticesCount - 1) / 2);
    for (size_t i = 0; i < verticesCount; ++i)
        for (size_t j = i + 1; j < verticesCount; ++j)
            edges.emplace_back(i, j);

    std::mt19937 rng(std::random_device{}());
    std::shuffle(edges.begin(), edges.end(), rng);

    edges.resize(edgesCount);

    for (const auto &e : edges) {
        res.addEdge(e.first, e.second);
    }

    return res;
}