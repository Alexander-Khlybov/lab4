#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <limits>
#include <iostream>
#include "priority_queue.hpp"
const size_t MAX_VERTICE_NUM = 100;
const double _INFINITY_ = std::numeric_limits<double>::infinity();


class DISTANCE {
public:
	int vertex;
	double distance;
    DISTANCE(int v, double d) : vertex(v), distance(d) {}
};

class GRAPH{
	double** dist_;
	size_t vertices_;
public:
    GRAPH(size_t max_num_of_vert = 10);
	GRAPH(const GRAPH&);
	~GRAPH(void);

	void    setDistance         (size_t, size_t, double);
	double  getDistance         (size_t, size_t)const;
    int     getNumOfVertices    (void)const { return vertices_; }
    double  getInf              (void)const { return _INFINITY_;}
};

#endif