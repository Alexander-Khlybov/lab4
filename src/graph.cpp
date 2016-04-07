#include "..\include\graph.h"

GRAPH::GRAPH(size_t max_num_of_vert){
    if ((max_num_of_vert > MAX_VERTICE_NUM) || (max_num_of_vert == 0))
        throw std::out_of_range("Out of range.");

    vertices_ = max_num_of_vert;

    dist_ = new double*[max_num_of_vert];
    if (dist_ == NULL)
        throw std::bad_alloc();

    for (size_t i = 0; i < max_num_of_vert; i++) {
        dist_[i] = new double[max_num_of_vert - i];
        if (dist_[i] == NULL)
            throw std::bad_alloc();
    }

    for (size_t i = 0; i < max_num_of_vert; i++) {
        for (size_t j = i; j < max_num_of_vert; j++)
            dist_[i][j] = 0;
    }

}

GRAPH::GRAPH(const GRAPH& graph){
    vertices_ = graph.vertices_;

    dist_ = new double*[vertices_];
    if (dist_ == NULL)
        throw std::bad_alloc();

    for (size_t i = 0; i < vertices_; i++) {
        dist_[i] = new double[vertices_ - i];
        if (dist_[i] == NULL)
            throw std::bad_alloc();
    }

    for (size_t i = 0; i < vertices_; i++) {
        for (size_t j = i; j < vertices_; j++)
            dist_[i][j] = graph.dist_[i][j];
    }
}

GRAPH::~GRAPH(void){
    for (size_t i = 0; i < vertices_; i++)
        delete[]dist_[i];
    delete[]dist_;
}

void GRAPH::setDistance(size_t first, size_t second, double dist){
    if ((first >= vertices_) || (second >= vertices_))
        throw std::out_of_range("Out of range.");

    if (first == second) {
        dist_[first][second] = 0;
        return;
    }

    if (first < second) {
        dist_[first][second] = dist;
        return;
    }
    dist_[second][first] = dist;
}

double GRAPH::getDistance(size_t first, size_t second) const{
    if ((first >= vertices_) || (second >= vertices_))
        throw std::out_of_range("Out of range.");
    return (first == second) ? 0 : ((first < second) ? 
        dist_[first][second] : dist_[second][first]);
}

void GRAPH::fillGraph(void){
    while (true) {
        size_t first = 0;
        std::cout << "Enter the first vertex: ";
        std::cin >> first;
        size_t second = 0;
        std::cout << "Enter the second vertex: ";
        std::cin >> second;
        double distance = 0;
        std::cout << "Enter the distance between the vertices: ";
        std::cin >> distance;
        setDistance(first, second, distance);
        char s;
        std::cout << "To complete the filling of the graph, type 'e': ";
        std::cin >> s;
        if (s == 'e')
            break;
    }
}

std::set<DISTANCE> GRAPH::getSetOfEdges(size_t currentVertex)const{
    if (currentVertex >= vertices_)
        throw std::out_of_range("Out of range.");

    std::set<DISTANCE> result;
    for (size_t i = 0; i < vertices_ - currentVertex; i++){
        if (dist_[currentVertex][i] != 0)
            result.insert(DISTANCE(i, dist_[currentVertex][i]));
    }

    for (size_t i = 1; i < vertices_ - currentVertex; i++){
        if(dist_[i][currentVertex] != 0)
            result.insert(DISTANCE(i, dist_[i][currentVertex]));
    }

    return result;
}
