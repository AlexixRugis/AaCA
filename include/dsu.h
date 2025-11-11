#pragma once

#include <vector>
#include <numeric>
#include <stdexcept>

class Dsu {
public:
    Dsu(size_t verticesCount) : mVerticesCount(verticesCount) {
        if (verticesCount == 0) {
            throw std::invalid_argument("vertices count must be positive.");
        }

        reset();
    }

    void reset() {
        mComponentsCount = mVerticesCount;
        mComponents.resize(mVerticesCount);
        std::iota(mComponents.begin(), mComponents.end(), 0);
    }

    size_t getComponentsCount() const {
        return mComponentsCount;
    }

    size_t get(size_t x) const {
        return mComponents[x];
    }

    void merge(size_t x, size_t y) {
        if (x != y) {
            mComponentsCount--;
        }

        for (auto& c : mComponents) {
            if (c == x) {
                c = y;
            }
        }
    }

private:
    size_t mVerticesCount;
    size_t mComponentsCount;
    std::vector<size_t> mComponents;
};