#pragma once

#include <stdexcept>
#include <vector>
#include <numeric>
#include "graph.h"

class NaiveAlgorithm {
public:
    NaiveAlgorithm(size_t verticesCount) : mVerticesCount(verticesCount) {
        if (verticesCount == 0) {
            throw std::invalid_argument("vertices count must be positive.");
        }

        mComponents.resize(verticesCount);
        std::iota(mComponents.begin(), mComponents.end(), 0);
    }

    void run(const Graph& g) {
        for (size_t iter = 0; iter <= mVerticesCount - 1; iter++) {
            for (const auto& edge : g) {
                size_t q = std::min(mComponents[edge.first], mComponents[edge.second]);
                mComponents[edge.first] = q;
                mComponents[edge.second] = q;
            }
        }
    }

    std::vector<size_t> getAns() const {
        return mComponents;
    }
private:
    size_t mVerticesCount;
    std::vector<size_t> mComponents;
};