#include <iostream>
#include <queue>
#include "Graph.hpp"

Graph::Graph(uint16_t amountOfVertices) {
    this->amountOfVertices = amountOfVertices;

    this->adjacencyMatrix = new uint16_t*[amountOfVertices];
    for (uint16_t i = 0; i < amountOfVertices; i++) {
        adjacencyMatrix[i] = new uint16_t[amountOfVertices];
        for (uint16_t j = 0; j < amountOfVertices; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }
}

Graph::~Graph() {
    delete(adjacencyMatrix);
}

void Graph::addEdge(uint16_t from, uint16_t to) {
    this->adjacencyMatrix[from - 1][to - 1] = 1;
}

void Graph::print() {
    std::cout << "Amount of vertices: " << amountOfVertices;
    for (uint16_t i = 0; i < amountOfVertices; i++) {
        auto currentList = adjacencyMatrix[i];
        std::cout << "Vertice " << i + 1 << ": ";
        for (uint16_t j = 0; j < amountOfVertices; j++) {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Graph::isNeighbor(uint16_t vertice) const {
    return vertice == 1;
}

bool Graph::swap(uint16_t commander, uint16_t commanded) {
    if (adjacencyMatrix[commander - 1][commanded -1] == 0) {
        std::cout << "Relation from " << commander << " to " << commanded << "does not exist." << std::endl;
        return false;
    }
    adjacencyMatrix[commander - 1][commanded - 1] = 0;
    adjacencyMatrix[commanded - 1][commander - 1] = 1;
    bool resultedInCycle = detectDirectedCycle();
    if (resultedInCycle) {
        std::cout << "This operation results in a cycle in the graph" << std::endl;
        adjacencyMatrix[commander - 1][commanded - 1] = 1;
        adjacencyMatrix[commanded - 1][commander - 1] = 0;
    }
    return !resultedInCycle;
}

bool Graph::detectDirectedCycle() {
    int *colors = new int[amountOfVertices];
    for (uint16_t i = 0; i < amountOfVertices; i++) {
        colors[i] = WHITE;
    }
    for (uint16_t i = 0; i < amountOfVertices; i++) {
        if (colors[i] == WHITE) {
            bool containsCycle = detectDirectedCycleHelper(i, colors);
            if (containsCycle) {
                return true;
            }
        }
    }
    return false;
}

bool Graph::detectDirectedCycleHelper(uint16_t vertice, int *colors) {
    colors[vertice] = GREY;
    //std::cout << "Current vertice: " << vertice << std::endl;
    auto neighbors = adjacencyMatrix[vertice];
    for (uint16_t i = 0; i < amountOfVertices; i++) {
        auto neighbor = neighbors[i];
        if (isNeighbor(neighbor)) {
            if (colors[i] == WHITE) {
                if (detectDirectedCycleHelper(i, colors)) {
                    return true;
                }
            } else if (colors[i] == GREY) {
                return true;
            }
        }
    }
    colors[vertice] = BLACK;
    return false;
}

uint16_t Graph::commander(uint16_t commanded, uint16_t* idades) {
    std::queue<uint16_t> filaComandados;
    filaComandados.push(commanded - 1);
    uint16_t minimumCommanderAge = 101;
    while (!filaComandados.empty()) {
        auto current = filaComandados.front();
        filaComandados.pop();

        for (uint16_t i = 0; i < amountOfVertices; i++) {
            // LOOK FOR DIRECT COMMANDERS
            if (adjacencyMatrix[i][current] == 1) { // i COMMANDS commanded
                minimumCommanderAge = std::min(minimumCommanderAge, idades[i]);
                filaComandados.push(i);
            }
        }
    }
    return minimumCommanderAge;
}

void Graph::meeting() {
    std::cout << "M ";
    // FIND NODES THAT ARE NOT COMMANDED BY ANYONE
    std::vector<uint16_t > inEdges(amountOfVertices, 0);
    for (uint16_t i = 0; i < amountOfVertices; i++) {
        for (uint16_t j = 0; j < amountOfVertices; j++) {
            if (adjacencyMatrix[j][i] == 1) { // EDGE ENTERING i
                inEdges[i]++;
            }
        }
    }
    std::queue<uint16_t> processingQueue;
    for (uint16_t i = 0; i < amountOfVertices; i++) {
        if (inEdges[i] == 0) {
            processingQueue.push(i);
        }
    }
    std::vector<uint16_t> result;
    while (!processingQueue.empty()) {
        auto current = processingQueue.front();
        processingQueue.pop();
        result.push_back(current);
        for (uint16_t i = 0; i < amountOfVertices; i++) {
            if (adjacencyMatrix[current][i] == 1) {
                inEdges[i]--;
                if (inEdges[i] == 0) {
                    processingQueue.push(i);
                }
            }
        }
    }

   for (uint16_t i = 0; i < amountOfVertices; i++) {
       std::cout << result[i] + 1 << " ";
   }
   std::cout << std::endl;
}


