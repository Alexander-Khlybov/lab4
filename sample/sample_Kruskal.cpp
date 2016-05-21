#include <iostream>
#include <string>
#include <algorithm>
#include "graph.h"
#include "algorithms.h"

int main(void) {

	size_t numVert = 1;
	std::cout << "\nEnter the number of vertices: ";
	std::cin >> numVert;

	//  *************|| FILLING OF GRAPH *************
	GRAPH graph(numVert);
	try {
		graph.fillGraph();
	}
	catch (exception& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}

	cout << "You can use priority queue based on D_HEAP, binary search tree (implemented as BST), SORT_TABLE.\nWhich algorithm do you want to use ?\n";
	string s;
	cin >> s;
	if (s != "D_HEAP" && s != "BST" && s != "SORT_TABLE") {
		cout << "Priority queue does not created.\n";
		return 1;
	}
	
	//  *************|| RESULT OUTPUT *************
	std::cout << "GRAPH: \n -------------------------";
	graph.graphInfo();
	std::cout << "Kruskal result: \n -------------------------";
	ALGORITHM::kruskal(graph, s).graphInfo();
	std::cout << "\n\n";

	getchar();
	return 0;
}