#include "..\include\graph.h"

GRAPH::GRAPH(size_t max_num_of_vert) : _INFINITY_(numeric_limits<double>::infinity()) {
}

GRAPH::GRAPH(const GRAPH& graph) : _INFINITY_(numeric_limits<double>::infinity()) {
}

GRAPH::~GRAPH(void){
}

void GRAPH::setDistance(size_t first, size_t second, double dist){
}

double GRAPH::getDistance(size_t first, size_t second) const{
    return 0;
}
