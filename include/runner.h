#pragma once

#include <iostream>
#include <ostream>
#include <chrono>
#include "graph.h"

enum class RunnerFeatures : size_t {
    SHOW_TIME = (size_t)1 << 0,
    SHOW_ANS = (size_t)1 << 1,
    VERBOSE = (size_t)1 << 2
};

constexpr RunnerFeatures operator|(RunnerFeatures a, RunnerFeatures b) {
    return static_cast<RunnerFeatures>(static_cast<size_t>(a) | static_cast<size_t>(b));
}

constexpr RunnerFeatures operator&(RunnerFeatures a, RunnerFeatures b) {
    return static_cast<RunnerFeatures>(static_cast<size_t>(a) & static_cast<size_t>(b));
}

template<typename T, RunnerFeatures FeatureMask = RunnerFeatures::SHOW_ANS | RunnerFeatures::SHOW_TIME |
RunnerFeatures::VERBOSE>
class Runner {
public:
    void run(const Graph& g, std::ostream& ostr) {
        T algoRunner(g.verticesCount());

        if (static_cast<size_t>(FeatureMask & RunnerFeatures::VERBOSE)) {
            ostr << "Running on graph with\nVertices: " << g.verticesCount() 
                << "\nEdges: " << g.edgesCount() << std::endl;
        }

        const auto start{std::chrono::steady_clock::now()};
        algoRunner.run(g);
        const auto finish{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_seconds{finish - start};

        if (static_cast<size_t>(FeatureMask & RunnerFeatures::SHOW_TIME)) {
            if (static_cast<size_t>(FeatureMask & RunnerFeatures::VERBOSE)) {
                ostr << "Run finished. Elapsed time: " << elapsed_seconds.count() << std::endl;
            }
            else {
                ostr << elapsed_seconds.count() << std::endl;
            }
        }

        if (static_cast<size_t>(FeatureMask & RunnerFeatures::SHOW_ANS)) {
            if (static_cast<size_t>(FeatureMask & RunnerFeatures::VERBOSE)) {
                auto result = algoRunner.getAns();
                ostr << "Result details:\nVertex\tComponent\n";
                for (size_t i = 0; i < g.verticesCount(); i++) {
                    ostr << i << '\t' << result[i] << '\n';
                }
                ostr.flush();
            }
            else {
                auto result = algoRunner.getAns();
                for (size_t c : result) {
                    ostr << c << ' ';
                }
                ostr << std::endl;
            }
        }
        
    }
};