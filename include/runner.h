#pragma once

#include <iostream>
#include <ostream>
#include <chrono>
#include "graph.h"

template<typename T>
class Runner {
public:
    void run(const Graph& g, std::ostream& ostr) {
        T algoRunner(g.verticesCount());

        ostr << "Running on graph with\nVertices: " << g.verticesCount() 
            << "\nEdges: " << g.edgesCount() << std::endl;

        const auto start{std::chrono::steady_clock::now()};
        algoRunner.run(g);
        const auto finish{std::chrono::steady_clock::now()};
        const std::chrono::duration<double> elapsed_seconds{finish - start};

        ostr << "Run finished. Elapsed time: " << elapsed_seconds.count() << std::endl;

        auto result = algoRunner.getAns();
        ostr << "Result details:\nVertex\tComponent\n";
        for (size_t i = 0; i < g.verticesCount(); i++) {
            ostr << i << '\t' << result[i] << '\n';
        }
        ostr.flush();
    }
};