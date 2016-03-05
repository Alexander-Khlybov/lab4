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