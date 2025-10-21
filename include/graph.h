#pragma once

#include <stdexcept>
#include <vector>

class Graph {
public:
    using Edge = std::pair<size_t, size_t>;
    using const_iterator = std::vector<Edge>::const_iterator;
    using const_reverse_iterator = std::vector<Edge>::const_reverse_iterator;

    Graph(size_t verticesCount) : mVerticesCount(verticesCount) {
        if (verticesCount == 0) {
            throw std::invalid_argument("vertices count must be positive.");
        }
    }

    void addEdge(size_t x, size_t y) {
        if (x >= mVerticesCount) {
            throw std::invalid_argument("vertex index 'x' is out of bounds.");
        }

        if (y >= mVerticesCount) {
            throw std::invalid_argument("vertex index 'y' is out of bounds.");
        }

        mEdges.emplace_back(x, y);
    }

    size_t verticesCount() const {
        return mVerticesCount;
    }

    size_t edgesCount() const {
        return mEdges.size();
    }

    const_iterator begin() const {
        return mEdges.begin();
    }

    const_iterator end() const {
        return mEdges.end();
    }

    const_reverse_iterator rbegin() const {
        return mEdges.rbegin();
    }

    const_reverse_iterator rend() const {
        return mEdges.rend();
    }

private:
    size_t mVerticesCount;
    std::vector<Edge> mEdges;
};