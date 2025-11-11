#include <iostream>
#include <fstream>

#include "graph.h"
#include "graph_generator.h"
#include "dsu.h"
#include "naive_algorithm.h"
#include "ram_algorithm.h"
#include "runner.h"


int main() {

    std::ifstream ifstr("input.txt");
    if (!ifstr.is_open()) {
        std::cout << "Expected input from input.txt. File not found!\n";
        return 0;
    }
    
    int n;
    ifstr >> n;

    const size_t RUNS = 10;
    size_t avg = 0;

    for (size_t i = 0; i < RUNS; i++) {
        Graph g = generateGraph(n, n * (n - 1) / 2);

        RamAlgorithm ramAlgorithm(n);
        size_t count = 0;
        if (ramAlgorithm.getCompCount() > 1) {
            for (const auto& edge : g) {
                ramAlgorithm.addEdge(edge);

                count++;
                if (ramAlgorithm.getCompCount() == 1) {
                    break;
                }
            }
        }

        avg += count;
    }

    std::ofstream ostrRam("output_ram.txt");

    ostrRam << avg / RUNS << std::endl;

    ostrRam.close();

    std::cout << "OK. You can see results in output_ram.txt\n";

    return 0;
}