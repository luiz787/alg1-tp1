#include <iostream>
#include "Graph.hpp"

Graph readInputAndBuildGraph();

int main() {
    auto graph = readInputAndBuildGraph();
    return 0;
}

Graph readInputAndBuildGraph() {
    uint16_t quantidadePessoas, quantidadeRelacoes, quantidadeInstrucoes;
    std::cin >> quantidadePessoas >> quantidadeRelacoes >> quantidadeInstrucoes;
    uint16_t idades[quantidadePessoas];
    auto graph = Graph(quantidadePessoas);
    for (uint8_t i = 0; i < quantidadePessoas; i++) {
        std::cin >> idades[i];
    }
    for (uint8_t i = 0; i < quantidadeRelacoes; i++) {
        uint16_t comandante;
        uint16_t comandado;
        std::cin >> comandante >> comandado;
        graph.addEdge(comandante, comandado);
    }
    for (uint8_t i = 0; i < quantidadeInstrucoes; i++) {
        char commandType;
        uint16_t minimumCommanderAge;
        std::cin >> commandType;
        switch (commandType) {
            case 'S':
                uint16_t commander, commanded;
                std::cin >> commander >> commanded;
                if (graph.swap(commander, commanded)) {
                    std::cout << "S T" << std::endl;
                } else {
                    std::cout << "S N" << std::endl;
                }
                break;
            case 'C':
                uint16_t a;
                std::cin >> a;
                minimumCommanderAge = graph.commander(a, idades);
                if (minimumCommanderAge != 101) {
                    std::cout << "C " << minimumCommanderAge << std::endl;
                } else {
                    std::cout << "C *" << std::endl;
                }
                break;
            case 'M':
                std::cout << "M" << std::endl;
                graph.meeting();
                break;
        }
    }
    graph.print();
    return graph;
}