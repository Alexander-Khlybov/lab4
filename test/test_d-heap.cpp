#include "d-heap.h"
#include <gtest.h>

TEST(D_HEAP, can_create_heap){

	ASSERT_NO_THROW(D_HEAP a(10, 3));
}

TEST(D_HEAP, throws_when_create_heap_with_size_less_than_0){
	
	ASSERT_ANY_THROW(D_HEAP a(-1, 3));
}

TEST(D_HEAP, throws_when_create_heap_with_D_equal_to_0){
	
	ASSERT_ANY_THROW(D_HEAP a(10, 0));
}

TEST(D_HEAP, throws_when_create_heap_with_D_less_than_0){
	
	ASSERT_ANY_THROW(D_HEAP a(10, -1));
}

TEST(D_HEAP, can_get_size_heap){
	D_HEAP a(10, 3);

	ASSERT_NO_THROW(a.getSizeTree());
}

TEST(D_HEAP, can_get_D){
	D_HEAP a(10, 3);
	ASSERT_NO_THROW(a.getD());
}

TEST(D_HEAP, getD_works_properly){
	D_HEAP a(10, 3);
	EXPECT_EQ(3, a.getD());
}

TEST(D_HEAP, created_heap_is_empty){
	D_HEAP a(10, 3);

	EXPECT_EQ(0, a.getSizeTree());
}

TEST(D_HEAP, compare_equal_heaps_return_true){
	D_HEAP a(10, 3);
	D_HEAP b(10, 3);

	for(int i = 0; i < 10; i++){
		a.insert(i);
		b.insert(i);
	}

	EXPECT_EQ(a, b);
}

TEST(D_HEAP, compare_non_equal_heaps_return_false){
	D_HEAP a(10, 3);
	D_HEAP b(10, 3);

	for(int i = 0; i < 9; i++){
		a.insert(i);
		b.insert(i);
	}
	a.insert(11);
	b.insert(12);

	EXPECT_NE(a, b);
}

TEST(D_HEAP, can_copy_heap){
	D_HEAP a(10, 3);

	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	ASSERT_NO_THROW(D_HEAP b(a));
}

TEST(D_HEAP, copied_heap_id_equal_to_source_one){
	D_HEAP a(10, 3);

	for(int i = 0; i < 10; i++){
		a.insert(i);
	}
	D_HEAP b(a);

	EXPECT_EQ(a, b);	
}

TEST(D_HEAP, can_get_node_key){
	D_HEAP a(10, 3);

	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	ASSERT_NO_THROW(a.getNodeKey(2));
}

TEST(D_HEAP, throws_when_get_node_key_with_negative_index){
	D_HEAP a(10, 3);

	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	ASSERT_ANY_THROW(a.getNodeKey(-1));
}

TEST(D_HEAP, throws_when_get_node_key_with_too_large_index){
	D_HEAP a(10, 3);

	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	ASSERT_ANY_THROW(a.getNodeKey(10));
}

TEST(D_HEAP, can_swap_two_nodes){
	D_HEAP a(10, 3);

	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	ASSERT_NO_THROW(a.swap(2, 3));
}

TEST(D_HEAP, throws_when_swap_with_negative_first_argument){
	D_HEAP a(10, 3);

	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	ASSERT_ANY_THROW(a.swap(-1, 2));
}

TEST(D_HEAP, throws_when_swap_with_negative_second_argument){
	D_HEAP a(10, 3);

	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	ASSERT_ANY_THROW(a.swap(1, -2));
}

TEST(D_HEAP, throws_when_swap_with_too_large_first_argument){
	D_HEAP a(10, 3);

	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	ASSERT_ANY_THROW(a.swap(10, 2));
}

TEST(D_HEAP, throws_when_swap_with_too_large_second_argument){
	D_HEAP a(10, 3);

	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	ASSERT_ANY_THROW(a.swap(1, 10));
}

TEST(D_HEAP, can_get_tree){
	D_HEAP a(10, 3);
	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	ASSERT_NO_THROW(a.getTree());
}

TEST(D_HEAP, getTree_works_properly){
	D_HEAP a(10, 3);
	TVector treeExp(10);
	for(int i = 0; i < 10; i++){
		a.insert(i);
		treeExp[i];
	}
	TVector tree = a.getTree();
	EXPECT_EQ(treeExp, tree);
}

TEST(D_HEAP, swap_works_properly){
	D_HEAP a(10, 3);
	TVector treeExp(10);
	for(int i = 0; i < 10; i++){
		a.insert(i);
		treeExp[i];
	}

	treeExp[0] = 2;
	treeExp[2] = 0;
	a.swap(0, 2);

	TVector tree = a.getTree();

	EXPECT_EQ(treeExp, tree);
}

TEST(D_HEAP, can_get_size_of_reserved_memory){
	D_HEAP a(10, 3);
	for(int i = 0; i < 7; i++){
		a.insert(i);
	}

	ASSERT_NO_THROW(a.getSizeReservedMem());
}

TEST(D_HEAP, getSizeReservedMem_works_properly){
	D_HEAP a(10, 3);
	for(int i = 0; i < 7; i++){
		a.insert(i);
	}

	EXPECT_EQ(3, a.getSizeReservedMem());
}

TEST(D_HEAP, can_sift_up_node){
	D_HEAP a(10, 3);
	TVector treeExp(10);
	for(int i = 0; i < 10; i++){
		a.insert(i);
		treeExp[i];
	}

	a.swap(0, 9);
	ASSERT_NO_THROW(a.siftUp(9));
}

TEST(D_HEAP, siftUp_throws_when_index_less_than_0){
	D_HEAP a(10, 3);
	TVector treeExp(10);
	for(int i = 0; i < 10; i++){
		a.insert(i);
		treeExp[i];
	}

	a.swap(0, 9);
	ASSERT_NO_THROW(a.siftUp(-1));
}

TEST(D_HEAP, siftUp_throws_when_index_is_too_large){
	D_HEAP a(10, 3);
	TVector treeExp(10);
	for(int i = 0; i < 10; i++){
		a.insert(i);
		treeExp[i];
	}

	a.swap(0, 9);
	ASSERT_NO_THROW(a.siftUp(10));
}

TEST(D_HEAP, siftUp_works_properly){
	D_HEAP a(10, 3);
	TVector treeExp(10);
	for(int i = 0; i < 10; i++){
		a.insert(i);
		treeExp[i];
	}

	treeExp[2] = 9;
	treeExp[9] = 2;

	a.swap(0, 9);
	a.siftUp(9);

	EXPECT_EQ(treeExp, a.getTree());
}

TEST(D_HEAP, can_sift_down_node){
	D_HEAP a(10, 3);
	TVector treeExp(10);
	for(int i = 0; i < 10; i++){
		a.insert(i);
		treeExp[i];
	}

	a.swap(0, 9);

	ASSERT_NO_THROW(a.siftDown(0));
}

TEST(D_HEAP, siftDown_throws_when_index_less_than_0){
	D_HEAP a(10, 3);
	TVector treeExp(10);
	for(int i = 0; i < 10; i++){
		a.insert(i);
		treeExp[i];
	}

	a.swap(0, 9);
	ASSERT_NO_THROW(a.siftDown(-1));
}

TEST(D_HEAP, siftDown_throws_when_index_is_too_large){
	D_HEAP a(10, 3);
	TVector treeExp(10);
	for(int i = 0; i < 10; i++){
		a.insert(i);
		treeExp[i];
	}

	a.swap(0, 9);
	ASSERT_NO_THROW(a.siftDown(10));
}

TEST(D_HEAP, siftDown_works_properly){
	D_HEAP a(10, 3);
	TVector treeExp(10);
	for(int i = 0; i < 10; i++){
		a.insert(i);
		treeExp[i];
	}


	a.swap(0, 4);
	a.siftDown(0);

	treeExp[0] = 1;
	treeExp[1] = 0;

	EXPECT_EQ(treeExp, a.getTree());
}

TEST(D_HEAP, can_insert_node){
	D_HEAP a(10, 3);
	ASSERT_NO_THROW(a.insert(1));
}

TEST(D_HEAP, insert_increases_size_tree){
	D_HEAP a(10, 3);
	int tmp = a.getSizeTree();
	a.insert(1);

	EXPECT_EQ(tmp + 1, a.getSizeTree());
}

TEST(D_HEAP, insert_can_allocate_memory){
	D_HEAP a(10, 3);
	for(int i = 0; i < 10; i++){
		a.insert(i);
	}
	int tmp = a.getSizeReservedMem();
	a.insert(10);

	EXPECT_EQ(tmp + a.getD() - 1, a.getSizeReservedMem());
}

TEST(D_HEAP, insert_can_allocate_any_number_of_memory){
	D_HEAP a(10, 3);
	for(int i = 0; i < 10; i++){
		a.insert(i);
	}
	int tmp = a.getSizeReservedMem();
	a.insert(10, ALLOW_MEMORY_REALLOCATION_WYV, 4);
	EXPECT_EQ(3, a.getSizeReservedMem());
}

TEST(D_HEAP, throws_when_insert_in_full_heap_with_key_PROHIBIT_MEMORY_REALLOCATION){
	D_HEAP a(10, 3);
	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	ASSERT_ANY_THROW(a.insert(10, PROHIBIT_MEMORY_REALLOCATION));
}

TEST(D_HEAP, insert_works_properly){
	D_HEAP a(10, 3);
	TVector treeExp(11);
	for(int i = 0; i < 10; i++){
		a.insert(i);
		treeExp[i];
	}

	treeExp[0] = -1;
	treeExp[3] = 0;
	treeExp[10] = 3;
	a.insert(-1);
	EXPECT_EQ(treeExp, a.getTree());
}

TEST(D_HEAP, can_delete_min_node){
	D_HEAP a(10, 3);
	for(int i = 0; i < 10; i++){
		a.insert(i);
	}
	ASSERT_NO_THROW(a.deleteMinElem());
}

TEST(D_HEAP, deleteMinElem_decreases_size_tree){
	D_HEAP a(10, 3);
	for(int i = 0; i < 10; i++){
		a.insert(i);
	}
	int tmp = a.getSizeTree();
	a.deleteMinElem();

	EXPECT_EQ(tmp - 1, a.getSizeTree());
}

TEST(D_HEAP, cant_delete_min_elem_from_empty_tree){
	D_HEAP a(10, 3);
	ASSERT_ANY_THROW(a.deleteMinElem());
}

TEST(D_HEAP, deleteMinElem_works_properly){
	D_HEAP a(10, 3);
	TVector temp[9];
	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	a.deleteMinElem();
	temp[0] = 1;
	temp[1] = 4;
	temp[2] = 2;
	temp[3] = 3;
	temp[4] = 9;
	temp[5] = 5;
	temp[6] = 6;
	temp[7] = 7;
	temp[8] = 8;

	EXPECT_EQ(tree, a.getTree());
}

TEST(D_HEAP, can_delete_elem){
	D_HEAP a(10, 3);
	for(int i = 0; i < 10; i++){
		a.insert(i);
	}
	ASSERT_NO_THROW(a.deleteElem(2));
}

TEST(D_HEAP, deleteElem_decreases_size_tree){
	D_HEAP a(10, 3);
	for(int i = 0; i < 10; i++){
		a.insert(i);
	}
	int tmp = a.getSizeTree();
	a.deleteElem();

	EXPECT_EQ(tmp - 1, a.getSizeTree(2));
}

TEST(D_HEAP, cant_delete_elem_from_empty_tree){
	D_HEAP a(10, 3);
	ASSERT_ANY_THROW(a.deleteElem(2));
}

TEST(D_HEAP, deleteElem_works_properly){
	D_HEAP a(10, 3);
	TVector temp[9];
	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	a.deleteElem(2);
	temp[0] = 0;
	temp[1] = 1;
	temp[2] = 7;
	temp[3] = 3;
	temp[4] = 4;
	temp[5] = 5;
	temp[6] = 6;
	temp[7] = 9;
	temp[8] = 8;

	EXPECT_EQ(tree, a.getTree());
}

TEST(D_HEAP, throws_when_delete_elem_with_negative_index){
	D_HEAP a(10, 3);
	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	ASSERT_ANY_THROW(a.deleteElem(-1));
}

TEST(D_HEAP, throws_when_delete_elem_with_too_large_index){
	D_HEAP a(10, 3);
	for(int i = 0; i < 10; i++){
		a.insert(i);
	}

	ASSERT_ANY_THROW(a.deleteElem(10));
}