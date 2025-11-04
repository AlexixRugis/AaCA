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

    Graph g(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        ifstr >> x >> y;
        g.addEdge(x, y);
    }

    Runner<NaiveAlgorithm, RunnerFeatures::SHOW_ANS | RunnerFeatures::SHOW_TIME> runnerNaive;
    Runner<RamAlgorithm, RunnerFeatures::SHOW_ANS | RunnerFeatures::SHOW_TIME> runnerRam;

    std::ofstream ostrNaive("output_naive.txt");
    std::ofstream ostrRam("output_ram.txt");

    runnerNaive.run(g, ostrNaive);
    runnerRam.run(g, ostrRam);

    ostrNaive.close();
    ostrRam.close();

    std::cout << "OK. You can see results in output_naive.txt and output_ram.txt\n";

    return 0;
}