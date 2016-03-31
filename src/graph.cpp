#include "..\include\graph.h"

GRAPH::GRAPH(size_t max_num_of_vert){
    if ((max_num_of_vert > MAX_VERTICE_NUM) || (max_num_of_vert == 0))
        throw std::out_of_range("Out of range.");

    vertices_ = max_num_of_vert;

    dist_ = new double*[max_num_of_vert - 1];
    if (dist_ == NULL)
        throw std::bad_alloc();

    for (size_t i = 0; i < max_num_of_vert - 1; i++) {
        dist_[i] = new double[max_num_of_vert - i - 1];
        if (dist_[i] == NULL)
            throw std::bad_alloc();
    }

    for (size_t i = 0; i < max_num_of_vert - 1; i++) {
        for (size_t j = i; j < max_num_of_vert - 1; j++)
            dist_[i][j] = 0;
    }

}

GRAPH::GRAPH(const GRAPH& graph){
    vertices_ = graph.vertices_;

    dist_ = new double*[vertices_ - 1];
    if (dist_ == NULL)
        throw std::bad_alloc();

    for (size_t i = 0; i < vertices_ - 1; i++) {
        dist_[i] = new double[vertices_ - i - 1];
        if (dist_[i] == NULL)
            throw std::bad_alloc();
    }

    for (size_t i = 0; i < vertices_ - 1; i++) {
        for (size_t j = i; j < vertices_ - 1; j++)
            dist_[i][j] = graph.dist_[i][j];
    }
}

GRAPH::~GRAPH(void){
    for (size_t i = 0; i < vertices_ - 1; i++)
        delete[]dist_[i];
    delete[]dist_;
}

void GRAPH::setDistance(size_t first, size_t second, double dist){
    if ((first >= vertices_) || (second >= vertices_))
        throw std::out_of_range("Ouet of range.");
    dist_[first][second] = dist;
}

double GRAPH::getDistance(size_t first, size_t second) const{
    if ((first >= vertices_) || (second >= vertices_))
        throw std::out_of_range("Ouet of range.");
    return dist_[first][second];
}
