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
    inputFile.close();
    return 0;
}

void readInputAndBuildGraph(std::ifstream* inputFile) {
    uint16_t amountOfPeople, amountOfRelations, amountOfInstructions;
    *inputFile >> amountOfPeople >> amountOfRelations >> amountOfInstructions;
    uint16_t ages[amountOfPeople];
    auto graph = Graph(amountOfPeople);
    for (uint8_t i = 0; i < amountOfPeople; i++) {
        *inputFile >> ages[i];
    }
    for (uint8_t i = 0; i < amountOfRelations; i++) {
        uint16_t commander;
        uint16_t commanded;
        *inputFile >> commander >> commanded;
        graph.addEdge(commander, commanded);
    }
    for (uint8_t i = 0; i < amountOfInstructions; i++) {
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
                minimumCommanderAge = graph.commander(a, ages);
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