#pragma once

#include <stdexcept>
#include <vector>
#include <numeric>
#include "graph.h"
#include "dsu.h"

class RamAlgorithm {
public:
    RamAlgorithm(size_t verticesCount) : mVerticesCount(verticesCount), mDsu(verticesCount) {
        if (verticesCount == 0) {
            throw std::invalid_argument("vertices count must be positive.");
        }
    }

    void reset() {
        mDsu.reset();
    }

    void addEdge(const Graph::Edge& e) {
        mDsu.merge(mDsu.get(e.first), mDsu.get(e.second));
    }

    void run(const Graph& g) {
        for (const auto& edge : g) {
            addEdge(edge);
        }
    }

    size_t getCompCount() const {
        return mDsu.getComponentsCount();
    }

    std::vector<size_t> getAns() const {
        std::vector<size_t> result(mVerticesCount);

        for (size_t i = 0; i < mVerticesCount; i++) {
            result[i] = mDsu.get(i);
        }

        return result;
    }
private:
    size_t mVerticesCount;
    Dsu mDsu;
};