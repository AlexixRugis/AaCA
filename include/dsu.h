#pragma once

#include <vector>
#include <numeric>
#include <stdexcept>

class DSU {
public:
    DSU(size_t verticesCount) : mVerticesCount(verticesCount) {
        if (verticesCount == 0) {
            throw std::invalid_argument("vertices count must be positive.");
        }

        mComponents.resize(verticesCount);
        std::iota(mComponents.begin(), mComponents.end(), 0);
    }

    size_t get(size_t x) const {
        return mComponents[x];
    }

    void merge(size_t x, size_t y) {
        for (auto& c : mComponents) {
            if (c == x) {
                c = y;
            }
        }
    }

private:
    size_t mVerticesCount;
    std::vector<size_t> mComponents;
};