#include <iostream>
#include <string>
#include <algorithm>
#include "priority_queue.hpp"
#include "disjoint-set.hpp"
#include "graph.h"
#include "algorithms.h"

//GRAPH	kruskal(const GRAPH&, const string&);
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

	cout << "You can use priority queue based on D_HEAP, AVL_TREE, SORT_TABLE.\nWhich algorithm do you want to use ?\n";
	string s;
	cin >> s;
	if (s != "D_HEAP" && s != "AVL_TREE" && s != "SORT_TABLE") {
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
//
//GRAPH kruskal(const GRAPH& graph, const string& s) {
//
//	DISJOINT_SET<int> g(graph.getNumOfVertices());
//	for (size_t i = 0; i < graph.getNumOfVertices(); i++)
//		g.createSet(i);
//	PRIORITY_QUEUE<EDGE>* queue;
//	if (s == "D_HEAP")
//		queue = new PRIORITY_QUEUE_ON_D_HEAP<EDGE>(3);
//	else if (s == "AVL_TREE")
//		queue = new PRIORITY_QUEUE_ON_AVL_TREE<EDGE>();
//	else
//		queue = new PRIORITY_QUEUE_ON_SORT_TABLE<EDGE>(graph.getAllEdges().size() + 1);
//	for (auto x : graph.getAllEdges()) {
//		queue->push(x);
//	}
//	GRAPH result(graph.getNumOfVertices());
//	while (g.getNumberOfSets() != graph.getNumOfComponents()) {
//		auto x = queue->back();
//		queue->pop();
//		size_t first = g.findSet(x.first);
//		size_t second = g.findSet(x.second);
//		if (first == second) continue;
//		g.uniteSets(first, second);
//		result.setDistance(x.first, x.second, x.distance);
//	}
//
//	cout << result.getNumOfVertices();
//	delete queue;
//	return result;
//}
