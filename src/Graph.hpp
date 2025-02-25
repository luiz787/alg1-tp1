#ifndef ALG1TP1_GRAPH_HPP
#define ALG1TP1_GRAPH_HPP

#include <list>
#include <cstdint>
#include <stack>
#include <vector>

enum COLOR { BLACK, GREY, WHITE };
class Graph {
private:
    uint16_t amountOfVertices;
    std::vector<std::list<uint16_t>> adjacencyLists;
    bool detectDirectedCycle();
    bool detectDirectedCycleHelper(uint16_t vertice, int* colors);
public:
    explicit Graph(uint16_t amountOfVertices);
    ~Graph();

    void addEdge(uint16_t from, uint16_t to);
    uint16_t commander(uint16_t commanded, uint16_t* idades);
    void meeting();
    bool swap(uint16_t commander, uint16_t commanded);

    std::vector<uint16_t> computeInEdges() const;
};


#endif
