#include <iostream>
#include "graph.h"
#include "priority_queue.hpp"
#include <vector>
#include <algorithm>

int main(void) {

    size_t numVert = 1;
    std::cout << "Enter the number of vertices: ";
    std::cin >> numVert;

    GRAPH* graph;
    try {
        graph = new GRAPH(numVert);
    }catch (exception& e) {
        std::cout << e.what() << std::endl;
        delete graph;
        return 1;
    }

    try {
        graph->fillGraph();
    }catch (exception& e) {
        std::cout << e.what() << std::endl;
        delete graph;
        return 1;
    }

    size_t currentVertex = 0;
    std::cout << "Enter the current vertex: ";
    std::cin >> currentVertex;

    if (currentVertex >= numVert) {
        std::cout << "Vertex does not exist.\n";
        return 1;
    }

    std::vector<DISTANCE> dist(numVert);
    size_t n = 0;
    std::for_each(dist.begin(), dist.end(), [&n](DISTANCE d) { 
        d.vertex = n++; d.distance = _INFINITY_;});
    PRIORITY_QUEUE<DISTANCE> queue;
    dist[currentVertex].distance = 0;
    std::for_each(dist.begin(), dist.end(), [&queue](DISTANCE d) {queue.push(d);});

    size_t* up = new size_t[numVert];
    for (size_t i = 0; i < numVert; i++) {
        up[i] = 0;
    }

    size_t numberOfEdges = 0;
    for (size_t i = 0; i < numVert; i++) {
        for (size_t j = i + 1; i < numVert; j++) {
            if (graph->getDistance(i, j) != 0)
                numberOfEdges += 1;
        }
    }
    cout << "1\n";

    std::pair<size_t, size_t>* edges = new pair<size_t, size_t>[numberOfEdges];
    size_t k = 0;
    for (size_t i = 0; i < numVert; i++) {
        for (size_t j = i; i < numVert; j++) {
            if (graph->getDistance(i, j) != 0) {
                edges[k].first = i;
                edges[k].second = j;
                k += 1;
            }
        }
    }

    while (!queue.isEmpty()) {
        DISTANCE d = queue.back();
        queue.pop();
        int V0 = -1;
        int V = d.vertex;

        for (size_t i = 0; i < numberOfEdges; i++) { // edges
            V0 = (edges[i].first == V) ? edges[i].second: (edges[i].second == V) ? edges[i].first : -1;
            if (V0 == -1) continue;
            if ((dist[V0].distance - dist[V].distance +
                graph->getDistance(V, V0)) > 0) {
                dist[V0].distance += graph->getDistance(V, V0);
                up[V0] = V;
            }
        }
    }

    std::cout << "Dijkstra result: \n -------------------------";
    std::cout << "Current vertex: " << currentVertex << "\n ===========================";
    std::cout << "Vertex:\t";
    for (size_t i = 0; i < numVert; i++) {
        if(dist[i].vertex != currentVertex)
            std::cout << dist[i].vertex << "\t";
    }

    std::cout << "\nDistance:\t";
    for (size_t i = 0; i < numVert; i++) {
        if (dist[i].vertex != currentVertex)
            std::cout << dist[i].distance << "\t";
    }

    std::cout << "\n\n";

    delete graph;
    delete[]edges;
    return 0;
}