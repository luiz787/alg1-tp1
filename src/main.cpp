#include <iostream>
#include <fstream>
#include "Graph.hpp"
#include <chrono>
#include <iomanip>
#include <ctime>

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
    std::cout << "Number of clock ticks per second = " << CLOCKS_PER_SEC << '\n';
    std::cout << "Time between clock ticks = " << 1.0 / CLOCKS_PER_SEC << " s\n\n";
    clock_t c_start = clock();
    auto t1 = std::chrono::high_resolution_clock::now(); // Inicia o relógio.
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
    clock_t c_end = clock();
    auto t2 = std::chrono::high_resolution_clock::now(); // Para o relógio.
    auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1); // Calcula o tempo gasto.
    double time_taken = double(c_end - c_start) / double(CLOCKS_PER_SEC);
    std::cout << std::setprecision(10) << "Time taken: " << time_taken << std::endl;
    std::cout << std::setprecision(10) << "Tempo:" << elapsedTime.count();
    std::cout << "This vitally-important calculation took " << 1000.0 * ( c_end - c_start ) / CLOCKS_PER_SEC << " ms\n";
}