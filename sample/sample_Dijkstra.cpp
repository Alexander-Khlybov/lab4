#include <iostream>
#include <algorithm>
#include "graph.h"
#include "algorithms.h"

int main(void) {

	size_t numVert = 1;
	std::cout << "\nEnter the number of vertices: ";
	std::cin >> numVert;

	//  *************|| FILLING OF GRAPH *************
	GRAPH* graph;
	try {
		graph = new GRAPH(numVert);
	}
	catch (exception& e) {
		std::cout << e.what() << std::endl;
		delete graph;
		return 1;
	}

	try {
		graph->fillGraph();
	}
	catch (exception& e) {
		std::cout << e.what() << std::endl;
		delete graph;
		return 1;
	}

	//  *************|| LABEL *************
	size_t currentVertex = 0;
	std::cout << "\nEnter the current vertex: ";
	std::cin >> currentVertex;
	if (currentVertex >= numVert) {
		std::cout << "\nVertex does not exist.\n";
		delete graph;
		return 1;
	}

	std::vector<DISTANCE> dist = ALGORITHM::dijkstra(*graph, currentVertex);
	//  *************|| RESULT OUTPUT *************
	graph->graphInfo();

	std::cout << "Dijkstra result: \n -------------------------";
	std::cout << "Current vertex: " << currentVertex << "\n ===========================";
	std::cout << "\nVertices:\t";
	for (size_t i = 0; i < dist.size(); i++) std::cout << i << "\t";
	cout << "\n\t\t";
	for (auto x : dist) std::cout << x.vertex << "\t";
	std::cout << "\nDistances:\t";
	for (auto x : dist) std::cout << x.distance << "\t";
	std::cout << "\n\n";

	delete graph;
	getchar();
	return 0;
}

