#include <iostream>
#include <queue>
#include "Graph.hpp"

Graph::Graph(uint16_t amountOfVertices) {
    this->amountOfVertices = amountOfVertices;
    this->adjacencyLists = new std::list<uint16_t>[amountOfVertices];
}

Graph::~Graph() {
    delete(adjacencyLists);
}

void Graph::addEdge(uint16_t from, uint16_t to) {
    this->adjacencyLists[from - 1].push_back(to);
}

void Graph::print() {
    /*std::cout << "Amount of vertices: " << amountOfVertices;
    for (uint16_t i = 0; i < amountOfVertices; i++) {
        auto currentList = adjacencyMatrix[i];
        std::cout << "Vertice " << i + 1 << ": ";
        for (uint16_t j = 0; j < amountOfVertices; j++) {
            std::cout << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }*/
}

bool Graph::isNeighbor(uint16_t vertice) const {
    return vertice == 1;
}

bool Graph::swap(uint16_t commander, uint16_t commanded) {
    auto adjacencyList = adjacencyLists[commander - 1];
    auto iterator = adjacencyList.begin();
    bool edgeExists = false;
    while (iterator != adjacencyList.end()) {
        if (*iterator == commanded) {
            adjacencyList.erase(iterator);
            edgeExists = true;
            break;
        }
    }
    if (edgeExists) {
        adjacencyLists[commanded - 1].push_back(commander - 1);
    } else {
        std::cout << "Relation from " << commander << " to " << commanded << "does not exist." << std::endl;
        return false;
    }
    bool resultedInCycle = detectDirectedCycle();
    if (resultedInCycle) {
        std::cout << "This operation results in a cycle in the graph" << std::endl;
        auto adjListCommanded = adjacencyLists[commanded - 1];
        iterator = adjListCommanded.begin();
        while (iterator != adjListCommanded.end()) {
            if (*iterator == commander) {
                adjListCommanded.erase(iterator);
                break;
            }
        }
        adjacencyLists[commander - 1].push_back(commanded - 1);
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
    std::list<uint16_t> neighbors = adjacencyLists[vertice];
    for (auto iterator = neighbors.begin(); iterator != neighbors.end(); ++iterator) {
        auto neighbor = *iterator;
        if (isNeighbor(neighbor)) {
            if (colors[*iterator] == WHITE) {
                if (detectDirectedCycleHelper(*iterator, colors)) {
                    return true;
                }
            } else if (colors[*iterator] == GREY) {
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
            for (auto& item : adjacencyLists[i]) {
                if (item == current) { // Item commands current
                    minimumCommanderAge = std::min(minimumCommanderAge, idades[item]);
                    filaComandados.push(item);
                }
            }

            // LOOK FOR DIRECT COMMANDERS
            /*if (adjacencyMatrix[i][current] == 1) { // i COMMANDS commanded
                minimumCommanderAge = std::min(minimumCommanderAge, idades[i]);
                filaComandados.push(i);
            }*/
        }
    }
    return minimumCommanderAge;
}

void Graph::meeting() {
    std::cout << "M ";
    // FIND NODES THAT ARE NOT COMMANDED BY ANYONE
    std::vector<uint16_t > inEdges(amountOfVertices, 0);
    for (uint16_t i = 0; i < amountOfVertices; i++) {
        for (auto& item : adjacencyLists[i]) {
            inEdges[item]++;
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
            for (auto& item : adjacencyLists[current]) {
                inEdges[item]--;
                if (inEdges[item] == 0) {
                    processingQueue.push(item);
                }
            }
    }

   for (uint16_t i = 0; i < amountOfVertices; i++) {
       std::cout << result[i] + 1 << " ";
   }
   std::cout << std::endl;
}


