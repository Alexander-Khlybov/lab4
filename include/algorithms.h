#pragma once
#include <string>
#include <vector>
#include "priority_queue.hpp"
#include "disjoint-set.hpp"
#include "graph.h"
using namespace std;

class ALGORITHM {
public:
	static GRAPH			kruskal(const GRAPH&, const string&);
	static vector<DISTANCE> dijkstra(const GRAPH&, const string&);
	static void				sort(vector<int>&);
};