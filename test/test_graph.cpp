#include <gtest.h>
#include "graph.h"

TEST(GRAPH, can_create_graph){
	ASSERT_NO_THROW(GRAPH(3));
}

TEST(GRAPH, throws_when_created_graph_with_number_of_vertices_bigger_than_MAX_VERTICE_NUM){
	ASSERT_ANY_THROW(GRAPH(101));
}

TEST(GRAPH, can_get_set_of_edges){
	GRAPH g(10);
	ASSERT_NO_THROW(g.getAllEdges());
}

TEST(GRAPH, created_graph_is_empty){
	GRAPH g(10);
	EXPECT_EQ(0, g.getAllEdges().size());
}

TEST(GRAPH, can_fill_rand_graph){
	GRAPH g(10);
	ASSERT_NO_THROW(g.createGraph(10, 1, 5));
}

TEST(GRAPH, throws_when_filling_graph_with_incorrect_number_of_edges){
	GRAPH g(10);
	ASSERT_ANY_THROW(g.createGraph(8, 1, 5));
	ASSERT_ANY_THROW(g.createGraph(46, 1, 5));
}

TEST(GRAPH, can_copy_graph){
	GRAPH g(10);
	g.createGraph(10, 1, 5);
	ASSERT_NO_THROW(GRAPH g1(g));
}

TEST(GRAPH, copied_graph_is_equal_to_source_one){
	GRAPH g(10);
	g.createGraph(10, 1, 5);
	GRAPH g1(g);
	vector<EDGE>	v(g.getAllEdges().size()),
					v1(g1.getAllEdges().size());
	size_t i = 0;
	for(EDGE x : g.getAllEdges())
		v[i++] = x;
	i = 0;
	for(EDGE x : g1.getAllEdges())
		v1[i++] = x;

	for (i = 0; i < 10; i++){
		int f = v[i].first == v1[i].first &&
				v[i].second == v1[i].second &&
				v[i].distance == v1[i].distance;
		EXPECT_EQ(1, f);
	}
}

TEST(GRAPH, can_get_number_of_vertices){
	GRAPH g(10);
	g.createGraph(10, 1, 5);
	ASSERT_NO_THROW(g.getNumOfVertices());
}

TEST(GRAPH, getNumOfVertices_works_properly){
	GRAPH g(10);
	g.createGraph(10, 1, 5);
	EXPECT_EQ(10, g.getNumOfVertices());
}

TEST(GRAPH, can_set_edge_to_graph){
	GRAPH g(10);
	ASSERT_NO_THROW(g.setDistance(1, 2, 3));
}

TEST(GRAPH, throws_when_setDistance_have_incorrect_first_or_second_argument){
	GRAPH g(10);
	ASSERT_ANY_THROW(g.setDistance(1, 10, 1));
	ASSERT_ANY_THROW(g.setDistance(10, 1, 1));
}

TEST(GRAPH, can_get_distance){
	GRAPH g(10);
	g.createGraph(10, 1, 5);
	ASSERT_NO_THROW(g.getDistance(1, 2));
}

TEST(GRAPH, throws_when_getDistance_have_incorrect_first_or_second_argument){
	GRAPH g(10);
	g.createGraph(10, 1, 5);
	ASSERT_ANY_THROW(g.getDistance(1, 20));
	ASSERT_ANY_THROW(g.getDistance(10, 2));
}

TEST(GRAPH, getDistance_works_properly){
	GRAPH g(10);
	g.createGraph(10, -100, 100);
	g.setDistance(1, 2, 1);
	EXPECT_EQ(1, g.getDistance(1, 2));
}

TEST(GRAPH, can_erase_edge){
	GRAPH g(10);
	g.createGraph(10, -100, 100);
	g.setDistance(1, 2, 1);
	ASSERT_NO_THROW(g.eraseEdge(1, 2));
}

TEST(GRAPH, can_get_set_of_edges_from_vertex){
	GRAPH g(10);
	g.createGraph(10, -100, 100);
	for (size_t i = 1; i < 10; i++) {
		g.eraseEdge(0, i);
	}
	g.setDistance(0, 1, 1);
	g.setDistance(0, 3, 4);
	g.setDistance(0, 4, 5);
	g.setDistance(0, 6, 3);
	g.setDistance(0, 9, 2);

	ASSERT_NO_THROW(g.getSetOfEdges(0));
}
