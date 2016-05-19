#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "priority_queue.hpp"
#include "disjoint-set.hpp"
#include "graph.h"
using namespace std;

class ALGORITHM {
public:
	static GRAPH			kruskal(const GRAPH&, const string&);
	static vector<DISTANCE> dijkstra(const GRAPH&, size_t);
	static void				sort(vector<int>&);
};
