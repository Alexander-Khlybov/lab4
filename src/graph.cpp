#include "..\include\graph.h"

GRAPH::GRAPH(const GRAPH& graph){
    vertices_ = graph.vertices_;
	graph_ = graph.graph_;
}

void GRAPH::setDistance(size_t first, size_t second, double dist){
    if ((first >= vertices_) || (second >= vertices_))
        throw std::out_of_range("Out of range.");
    if(first == second) 
		return;

	for (EDGE x : graph_) {
		if (x.first == MIN(first, second) && x.second == MAX(first, second)) {
			graph_.erase(x);
			break;
		}
	}
	
	graph_.insert(EDGE(MIN(first, second),
					MAX(first, second), dist));
}

double GRAPH::getDistance(size_t first, size_t second) const{
    if ((first >= vertices_) || (second >= vertices_))
        throw std::out_of_range("Out of range.");
        if (first == second) return 0;
	double dist = 0;
	for (EDGE x : graph_) {
		if (x.first == first && x.second == second ||
			x.first == second && x.second == first) {
			dist = x.distance;
			break;
		}
	}
	return dist;
}

void GRAPH::eraseEdge(size_t first, size_t second){
	for (auto x : graph_) {
		if (first == x.first && second == x.second ||
			first == x.second && second == x.first) {
			graph_.erase(x);
			return;
		}
	}
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

std::multiset<DISTANCE> GRAPH::getSetOfEdges(size_t currentVertex)const{
    if (currentVertex >= vertices_)
        throw std::out_of_range("Out of range.");
	std::multiset<DISTANCE> result;
	for (size_t i = 0; i < vertices_; i++) {
		double dist = getDistance(i, currentVertex);
		if (dist != 0) result.insert(DISTANCE(i, dist));
	}
    return result;
}

void GRAPH::graphInfo(void)const{
	std::cout << "\n======== THE NUMBER OF VERTICES ========\n\n"
		<< vertices_ << std::endl;

	std::cout << "\n======== THE NUMBER OF EDGES    ========\n\n"
		<< graph_.size() << std::endl;

	std::cout << "\n=========== EDGES ===========\n\n";
	size_t i = 0;
	for (auto x : graph_) {
		std::cout << x.first << "<-->" << x.second
			<< "  ::  " << x.distance << "\t|||\n";
	}

	std::cout << "\n\n";
}
