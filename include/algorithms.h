#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "priority_queue.hpp"
#include "disjoint-set.hpp"
#include "graph.h"
using namespace std;

class MAKE_PRIORITY_QUEUE {
public:
	static void makeQueueBasedOn(PRIORITY_QUEUE<EDGE>*, const string&, size_t size = 0);
};

class ALGORITHM {
public:
	static GRAPH			kruskal(const GRAPH&, const string&);
	static vector<DISTANCE> dijkstra(const GRAPH&, size_t, const string&);
	static void				sort(vector<int>&);
};