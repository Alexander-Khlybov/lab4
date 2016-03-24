#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <limits>
using namespace std;
const size_t MAX_VERTICE_NUM = 100;

class GRAPH{
	double** dist_;
	size_t numberОfVertices_;
    const double _INFINITY_;
public:
    GRAPH(size_t max_num_of_vert = 10);
	GRAPH(const GRAPH&);
	~GRAPH(void);

	void    setDistance         (size_t, size_t, double);
	double  getDistance         (size_t, size_t)const;
    int     getNumOfVertices    (void)const { return numberОfVertices_; }
    double  getInf              (void)const { return _INFINITY_;}
};

#endif