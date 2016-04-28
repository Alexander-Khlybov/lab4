#include <iostream>
#include <algorithm>
#include "graph.h"
#include "disjoint-set.hpp"

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

	DISJOINT_SET<int> g(numVert);
	for (size_t i = 0; i < numVert; i++)
		g.createSet(i);

	PRIORITY_QUEUE<EDGE> queue;
	for (auto x : graph->getAllEdges()) {
		queue.push(x);
	}

	GRAPH* result;
	try {
		result = new GRAPH(numVert);
	}
	catch (exception& e) {
		std::cout << e.what() << std::endl;
		delete graph;
		delete result;
		return 1;
	}

	while (g.getNumberOfSets() != 1) {
		auto x = queue.back();
		queue.pop();
		g.uniteSets(g.findSet(x.first), g.findSet(x.second));
		result->setDistance(x.first, x.second, x.distance);
	}

	//  *************|| RESULT OUTPUT *************
	std::cout << "GRAPH: \n -------------------------";
	graph->graphInfo();
	std::cout << "Kruskal result: \n -------------------------";
	result->graphInfo();
	std::cout << "\n\n";

	delete graph;
	delete result;
	return 0;
}