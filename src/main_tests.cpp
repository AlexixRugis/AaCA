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
    

    int n, m;
    ifstr >> n >> m;

    Graph g = generateGraph(n, m);

    Runner<NaiveAlgorithm, RunnerFeatures::SHOW_TIME, 10> runnerNaive;
    Runner<RamAlgorithm, RunnerFeatures::SHOW_TIME, 10> runnerRam;

    std::ofstream ostrNaive("output_naive.txt");
    std::ofstream ostrRam("output_ram.txt");

    std::cout << "Running Naive Algorithm...\n";
    runnerNaive.run(g, ostrNaive);
    std::cout << "Running Ram Algorithm...\n";
    runnerRam.run(g, ostrRam);

    if (n <= 10) {
        for (auto e : g) {
            ostrNaive << e.first << ' ' << e.second << '\n';
            ostrRam << e.first << ' ' << e.second << '\n';
        }
    }

    ostrNaive.close();
    ostrRam.close();

    std::cout << "OK. You can see results in output_naive.txt and output_ram.txt\n";

    return 0;
}