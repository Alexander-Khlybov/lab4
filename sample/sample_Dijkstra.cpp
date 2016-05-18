#include <iostream>
#include <algorithm>
#include "graph.h"
#include "priority_queue.hpp"
#include "graph.h"
vector<DISTANCE> dijkstra(const GRAPH&, size_t, const string&);

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

	std::vector<DISTANCE> dist = dijkstra(*graph, currentVertex, "D_HEAP");
	cout << 1;
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

vector<DISTANCE> dijkstra(const GRAPH& graph, size_t currentVertex, const string& s) {
	vector<DISTANCE> dist(graph.getNumOfVertices());
	dist[currentVertex].distance = 0;
	dist[currentVertex].vertex = currentVertex;
	PRIORITY_QUEUE<DISTANCE>* queue = new PRIORITY_QUEUE_ON_D_HEAP<DISTANCE>(3);
	queue->push(dist[currentVertex]);
	while (!queue->isEmpty()) {
		DISTANCE d = queue->back();
		queue->pop();
		if (d.distance > dist[d.vertex].distance) continue;
		std::multiset<DISTANCE> a = graph.getSetOfEdges(d.vertex);
		for_each(a.begin(), a.end(), [&](DISTANCE k) {
			size_t tmp = k.vertex;
			double len = k.distance;
			if (dist[tmp].distance > dist[d.vertex].distance + len) {
				dist[tmp].vertex = d.vertex;
				dist[tmp].distance = dist[d.vertex].distance + len;
				queue->push(DISTANCE(tmp, dist[tmp].distance));
			}
		});
	}
	return dist;
}
