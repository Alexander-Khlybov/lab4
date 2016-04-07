#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include "graph.h"
#include "priority_queue.hpp"

int main(void) {

    size_t numVert = 1;
    std::cout << "Enter the number of vertices: ";
    std::cin >> numVert;

//  *************|| FILLING OF GRAPH *************
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

//  *************|| LABEL *************
    size_t currentVertex = 0;
    std::cout << "Enter the current vertex: ";
    std::cin >> currentVertex;
    if (currentVertex >= numVert) {
        std::cout << "Vertex does not exist.\n";
        delete graph;
        return 1;
    }

//  *************|| INITIAL VECTOR OF DISTANCES AND VISITED VERTICES *************
    std::vector<DISTANCE> dist(numVert);
    dist[currentVertex].vertex = currentVertex;
    dist[currentVertex].distance = 0;

//  *************|| INITIAL PRYORITY QUEUE *************
    PRIORITY_QUEUE<DISTANCE> queue;
    queue.push(DISTANCE(dist[currentVertex]));

//  *************|| DIJKSTRA CYCLE *************
    while(!queue.isEmpty()){
        DISTANCE d = queue.back();
        queue.pop();
        if (d > dist[d.vertex]) continue;
        std::set<DISTANCE> edges = graph->getSetOfEdges(d.vertex);
        for(DISTANCE k : edges){
            size_t tmp = k.vertex;
            double len = k.distance;
            if(dist[tmp].distance > dist[d.vertex].distance + len){
                dist[tmp].vertex = d.vertex;
                dist[tmp].distance = dist[d.vertex].distance + len;
                queue.push(DISTANCE(tmp, dist[tmp].distance));
            }
        }
    }

//  *************|| RESULT OUTPUT *************
    std::cout << "Dijkstra result: \n -------------------------";
    std::cout << "Current vertex: " << currentVertex << "\n ===========================";
    std::cout << "Vertex:\t";
    for (size_t i = 0; i < numVert; i++) {
        if(dist[i].vertex != currentVertex)
            std::cout << i << "\t";
    }

    std::cout << "\nDistance:\t";
    for (size_t i = 0; i < numVert; i++) {
        if (dist[i].vertex != currentVertex)
            std::cout << dist[i].distance << "\t";
    }
    std::cout << "\n\n";

    delete graph;
    return 0;
}
