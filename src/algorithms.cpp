#include "algorithms.h"


GRAPH ALGORITHM::kruskal(const GRAPH& graph, const string& s) {

	DISJOINT_SET<int> g(graph.getNumOfVertices());
	for (size_t i = 0; i < graph.getNumOfVertices(); i++)
		g.createSet(i);
	PRIORITY_QUEUE<EDGE>* queue;
	MAKE_PRIORITY_QUEUE<EDGE>::makeQueueBasedOn(queue, s, (s == "SORT_TABLE") ? graph.getAllEdges().size() + 1 : 3);
	for (auto x : graph.getAllEdges()) {
		queue->push(x);
	}
	GRAPH result(graph.getNumOfVertices());
	while (g.getNumberOfSets() != graph.getNumOfComponents()) {
		cout << 3;
		auto x = queue->back();
		queue->pop();
		size_t first = g.findSet(x.first);
		size_t second = g.findSet(x.second);
		if (first == second) continue;
		g.uniteSets(first, second);
		result.setDistance(x.first, x.second, x.distance);
	}
	delete queue;
	return result;
}

vector<DISTANCE> ALGORITHM::dijkstra(const GRAPH& graph, size_t currentVertex){
	vector<DISTANCE> dist(graph.getNumOfVertices());
	dist[currentVertex].distance = 0;
	dist[currentVertex].vertex = currentVertex;
	PRIORITY_QUEUE<DISTANCE>* queue;
	MAKE_PRIORITY_QUEUE<DISTANCE>::makeQueueBasedOn(queue, "D_HEAP", 3);
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

void ALGORITHM::sort(vector<int>& v){
	D_HEAP<int> heap(v.size(), 3);
	for (int x : v) {
		heap.insert(x, PROHIBIT_MEMORY_REALLOCATION);
	}
	for (size_t i = 0; i < v.size(); i++) {
		v[i] = heap.getNodeKey(0);
		heap.deleteMinElem();
	}
}
