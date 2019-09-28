#include <iostream>
#include <fstream>
#include "Graph.hpp"

void readInputAndBuildGraph(std::ifstream* inputFile);

int main(int argc, char** argv) {
    char* inputFileName = argv[1];
    std::ifstream inputFile (inputFileName);
    if (!inputFile.is_open()) {
        std::cout << "Falha ao abrir o arquivo de entrada." << std::endl;
        return 1;
    }
    readInputAndBuildGraph(&inputFile);
    return 0;
}

void readInputAndBuildGraph(std::ifstream* inputFile) {
    uint16_t quantidadePessoas, quantidadeRelacoes, quantidadeInstrucoes;
    *inputFile >> quantidadePessoas >> quantidadeRelacoes >> quantidadeInstrucoes;
    uint16_t idades[quantidadePessoas];
    auto graph = Graph(quantidadePessoas);
    for (uint8_t i = 0; i < quantidadePessoas; i++) {
        *inputFile >> idades[i];
    }
    for (uint8_t i = 0; i < quantidadeRelacoes; i++) {
        uint16_t comandante;
        uint16_t comandado;
        *inputFile >> comandante >> comandado;
        graph.addEdge(comandante, comandado);
    }
    for (uint8_t i = 0; i < quantidadeInstrucoes; i++) {
        char commandType;
        uint16_t minimumCommanderAge;
        *inputFile >> commandType;
        switch (commandType) {
            case 'S':
                uint16_t commander, commanded;
                *inputFile >> commander >> commanded;
                if (graph.swap(commander, commanded)) {
                    std::cout << "S T" << std::endl;
                } else {
                    std::cout << "S N" << std::endl;
                }
                break;
            case 'C':
                uint16_t a;
                *inputFile >> a;
                minimumCommanderAge = graph.commander(a, idades);
                if (minimumCommanderAge != 101) {
                    std::cout << "C " << minimumCommanderAge << std::endl;
                } else {
                    std::cout << "C *" << std::endl;
                }
                break;
            case 'M':
                graph.meeting();
                break;
        }
    }
}