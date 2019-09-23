#include <iostream>
#include <queue>
#include "Graph.hpp"

Graph::Graph(uint16_t amountOfVertices) {
    this->amountOfVertices = amountOfVertices;
    this->adjacencyLists = std::vector<std::list<uint16_t>>(amountOfVertices, std::list<uint16_t>());
}

Graph::~Graph() {
}

void Graph::addEdge(uint16_t from, uint16_t to) {
    this->adjacencyLists[from - 1].push_back(to - 1);
}

bool Graph::swap(uint16_t commander, uint16_t commanded) {
    bool edgeExists = false;
    for (auto const& item : adjacencyLists[commander - 1]) {
        if (item == commanded - 1) {
            edgeExists = true;
            break;
        }
    }
    if (edgeExists) {
        adjacencyLists[commander - 1].remove(commanded - 1);
        adjacencyLists[commanded - 1].push_back(commander - 1);
    } else {
        return false;
    }
    bool resultedInCycle = detectDirectedCycle();
    if (resultedInCycle) {
        adjacencyLists[commanded - 1].remove(commander - 1);
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
    for (auto& item : adjacencyLists[vertice]) {
        if (colors[item] == WHITE) {
            if (detectDirectedCycleHelper(item, colors)) {
                return true;
            }
        } else if (colors[item] == GREY) {
            return true;
        }
    }
    colors[vertice] = BLACK;
    return false;
}

uint16_t Graph::commander(uint16_t commanded, uint16_t* idades) {
    // traverse the adjacency list of given graph and
    // for each edge (u, v) add an edge (v, u) in the
    // transpose graph's adjacency list
    Graph transpose = Graph(amountOfVertices);
    for (uint16_t i = 0; i < amountOfVertices; i++) {
        for (auto &j : adjacencyLists[i]) {
            transpose.addEdge(j + 1, i + 1);
        }
    }
    uint16_t minimumCommanderAge = 101;
    std::queue<uint16_t> processingQueue;
    processingQueue.push(commanded - 1);
    while (!processingQueue.empty()) {
        auto currentVertice = processingQueue.front();
        processingQueue.pop();
        for (auto &vertice : transpose.adjacencyLists[currentVertice]) {
            processingQueue.push(vertice);
            minimumCommanderAge = std::min(minimumCommanderAge, idades[vertice]);
        }
    }
    return minimumCommanderAge;
}

void Graph::meeting() {
    std::cout << "M ";
    // FIND NODES THAT ARE NOT COMMANDED BY ANYONE
    std::vector<uint16_t> inEdges = computeInEdges();
    std::queue<uint16_t> processingQueue;
    for (uint16_t i = 0; i < amountOfVertices; i++) {
        if (inEdges[i] == 0) {
            processingQueue.push(i);
        }
    }
    std::vector<uint16_t> result;
    while (!processingQueue.empty()) {
        auto currentVertice = processingQueue.front();
        processingQueue.pop();
        result.push_back(currentVertice);
        for (auto& vertice : adjacencyLists[currentVertice]) {
            inEdges[vertice]--;
            if (inEdges[vertice] == 0) {
                processingQueue.push(vertice);
            }
        }
    }

   for (uint16_t i = 0; i < amountOfVertices; i++) {
       std::cout << result[i] + 1 << " ";
   }
   std::cout << std::endl;
}

std::vector<uint16_t> Graph::computeInEdges() const {
    std::vector<uint16_t> inEdges(amountOfVertices, 0);
    for (uint16_t i = 0; i < amountOfVertices; i++) {
        for (auto &vertice : adjacencyLists[i]) {
            inEdges[vertice]++;
        }
    }
    return inEdges;
}


