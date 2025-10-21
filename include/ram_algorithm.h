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

    void run(const Graph& g) {
        for (const auto& edge : g) {
            mDsu.merge(edge.first, edge.second);
        }
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