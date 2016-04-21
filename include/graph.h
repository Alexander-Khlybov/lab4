#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <limits>
#include <iostream>
#include <set>
#include "priority_queue.hpp"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))


const size_t MAX_VERTICE_NUM = 100;
const double _INFINITY_ = std::numeric_limits<double>::infinity();

class DISTANCE {
public:
	size_t vertex;
    double distance;

    DISTANCE(size_t v = 0, double d = _INFINITY_) : 
					vertex(v), distance(d) {}

    int operator==  (const DISTANCE& d)const { return (distance == d.distance) ? 1 : 0; }
    int operator!=  (const DISTANCE& d)const { return (distance != d.distance) ? 1 : 0; }
    int operator<   (const DISTANCE& d)const { return (distance < d.distance) ? 1 : 0; }
    int operator<=  (const DISTANCE& d)const { return (distance <= d.distance) ? 1 : 0; }
    int operator>   (const DISTANCE& d)const { return (distance > d.distance) ? 1 : 0; }
    int operator>=  (const DISTANCE& d)const { return (distance >= d.distance) ? 1 : 0; }
};

class GRAPH{
	std::set<pair<size_t, DISTANCE> > graph_;
	size_t vertices_;

public:
	GRAPH(size_t max_num_of_vert = 10) : vertices_(max_num_of_vert) {
					if ((max_num_of_vert > MAX_VERTICE_NUM) || (max_num_of_vert == 0))
						throw std::out_of_range("Out of range.");}

	GRAPH(const GRAPH&);
	~GRAPH(void) {}

	void    setDistance         (size_t, size_t, double);
	double  getDistance         (size_t, size_t)const;
    int     getNumOfVertices    (void)const { return vertices_; }
    double  getInf              (void)const { return _INFINITY_;}
    void    fillGraph           (void);

    std::set<DISTANCE> getSetOfEdges(size_t)const;

	void graphInfo(void)const;
};

#endif
