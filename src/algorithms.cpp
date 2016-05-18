#include "algorithms.h"

void MAKE_PRIORITY_QUEUE::makeQueueBasedOn(PRIORITY_QUEUE<EDGE>* q, const string& s, size_t size) {
	map<string, int> m;
	m["D_HEAP"] = 1;
	m["AVL_TREE"] = 2;
	m["SORT_TABLE"] = 3;
	switch (m.find(s)->second) {
	case 1:
		q = new PRIORITY_QUEUE_ON_D_HEAP<EDGE>(size);
		break;
	case 2:
		q = new PRIORITY_QUEUE_ON_AVL_TREE<EDGE>();
		break;
	case 3:
		q = new PRIORITY_QUEUE_ON_SORT_TABLE<EDGE>(size);
		break;
	default:
		throw exception("Priority queue does not created");
	}
}


GRAPH ALGORITHM::kruskal(const GRAPH &, const string &){
	return GRAPH();
}

vector<DISTANCE> ALGORITHM::dijkstra(const GRAPH& graph, size_t currentVertex, const string& s){
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
