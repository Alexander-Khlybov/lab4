#include "algorithms.h"

GRAPH ALGORITHM::kruskal(const GRAPH &, const string &){
	return GRAPH();
}

vector<DISTANCE> ALGORITHM::dijkstra(const GRAPH &, const string &){
	return vector<DISTANCE>();
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
