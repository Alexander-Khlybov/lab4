#include "..\include\graph.h"

GRAPH::GRAPH(const GRAPH& graph){
    vertices_ = graph.vertices_;
	graph_ = graph.graph_;
}

void GRAPH::setDistance(size_t first, size_t second, double dist){
    if ((first >= vertices_) || (second >= vertices_))
        throw std::out_of_range("Out of range.");
	graph_.insert(pair<size_t, DISTANCE>(MIN(first, second), 
					DISTANCE(MAX(first, second), dist)));
}

double GRAPH::getDistance(size_t first, size_t second) const{
    if ((first >= vertices_) || (second >= vertices_))
        throw std::out_of_range("Out of range.");
	double dist = 0;
	for (auto x : graph_) {
		if (x.first == first && x.second.vertex == second ||
			x.first == second && x.second.vertex == first) {
			dist = x.second.distance;
			break;
		}
	}
	return dist;
}

void GRAPH::fillGraph(void){
    while (true) {
        size_t first = 0;
        std::cout << "\nEnter the first vertex: ";
        std::cin >> first;
        size_t second = 0;
        std::cout << "\nEnter the second vertex: ";
        std::cin >> second;
        double distance = 0;
        std::cout << "\nEnter the distance between the vertices: ";
        std::cin >> distance;
        setDistance(first, second, distance);
        char s;
        std::cout << "\nTo complete the filling of the graph, type 'e': ";
        std::cin >> s;
        if (s == 'e')
            break;
    }
}

std::set<DISTANCE> GRAPH::getSetOfEdges(size_t currentVertex)const{
    if (currentVertex >= vertices_)
        throw std::out_of_range("Out of range.");
	std::set<DISTANCE> result;
	for (size_t i = 0; i < vertices_; i++) {
		double dist = getDistance(i, currentVertex);
		if (dist != 0) result.insert(DISTANCE(i, dist));
	}
    return result;
}

void GRAPH::graphInfo(void)const{
	std::cout << "\n=========== EDGES ===========\n\n";
	for (auto x : graph_) {
		std::cout << x.first << "<-->" << x.second.vertex 
			<< "  ::  " << x.second.distance << "\t|||\t";
	}
	std::cout << "\n\n";
}
