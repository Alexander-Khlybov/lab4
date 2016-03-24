#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <limits>
#include <iostream>
using namespace std;
const size_t MAX_VERTICE_NUM = 100;

class GRAPH{
	double** dist_;
	size_t vertices_;
    const double _INFINITY_;
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