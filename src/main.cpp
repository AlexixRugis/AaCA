#include <iostream>

#include "graph.h"
#include "dsu.h"
#include "naive_algorithm.h"
#include "ram_algorithm.h"
#include "runner.h"


int main() {
    int n, m;
    std::cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        g.addEdge(x, y);
    }

    Runner<RamAlgorithm> runnerNaive;
    runnerNaive.run(g, std::cout);
}