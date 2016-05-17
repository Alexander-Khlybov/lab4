#include "priority_queue.hpp"
#include <gtest.h>

TEST(PRIORITY_QUEUE_ON_D_HEAP, can_create_queue){
	PRIORITY_QUEUE<int>* a;

	ASSERT_NO_THROW(a = new PRIORITY_QUEUE_ON_D_HEAP<int>(2));
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, created_queue_is_empty){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(2);

	EXPECT_EQ(1, a.isEmpty());
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, can_get_size_queue){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(2);

	ASSERT_NO_THROW(a.getSize());
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, getSize_works_properly){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(2);

	EXPECT_EQ(0, a.getSize());
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, can_push_key){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(2);

	ASSERT_NO_THROW(a.push(1));
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, push_increases_size){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(2);
	int tmp = a.getSize();
	a.push(1);

	EXPECT_EQ(tmp + 1, a.getSize());
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, can_pop_elem){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(2);
	a.push(1);
	a.push(2);

	ASSERT_NO_THROW(a.pop());
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, throws_when_pop_from_empty){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(1);

	ASSERT_ANY_THROW(a.pop());
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, pop_decreases_size){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(2);
	a.push(1);
	a.push(2);
	int tmp = a.getSize();
	a.pop();

	EXPECT_EQ(tmp - 1, a.getSize());
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, can_get_back_elem){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(2);
	a.push(1);
	a.push(2);

	ASSERT_NO_THROW(a.back());
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, throws_when_back_from_empty){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(2);

	ASSERT_ANY_THROW(a.back());
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, back_dont_decrease_size){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(2);
	a.push(1);
	a.push(2);
	int tmp = a.getSize();
	a.back();

	EXPECT_EQ(tmp, a.getSize());
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, back_returns_elem_with_max_priority){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(2);
	for (int i = 10; i > -1; i--){
		a.push(i);
	}

	EXPECT_EQ(0, a.back());
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, push_works_properly){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(1);
	for (int i = 10; i > 0; i--){
		a.push(i % 3);
	}

	vector<int> b(10);
	for (int i = 0; i < 10; i++){
		b[i] = (i < 3) ? 0 : ((i < 7) ? 1 : 2);
	}

	vector<int> c = a.getHeap().getTree();

	EXPECT_EQ(b, c);
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, can_copy_queue){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(2);
	a.push(3);

	ASSERT_NO_THROW(PRIORITY_QUEUE_ON_D_HEAP<int> b(a));
}

TEST(PRIORITY_QUEUE_ON_D_HEAP, copied_queue_is_equal_to_source_one){
	PRIORITY_QUEUE_ON_D_HEAP<int> a(2);
	for (int i = 0; i < 10; i++){
		a.push(i);
	}
	vector<int> t1 = a.getHeap().getTree();
	PRIORITY_QUEUE_ON_D_HEAP<int> b(a);
	vector<int> t2 = b.getHeap().getTree();
	EXPECT_EQ(t1, t2);
}

TEST(PRIORITY_QUEUE_ON_AVL_TREE, can_create_queue){
	PRIORITY_QUEUE<int>* a;

	ASSERT_NO_THROW(a = new PRIORITY_QUEUE_ON_AVL_TREE<int>());
}

TEST(PRIORITY_QUEUE_ON_AVL_TREE, created_queue_is_empty){
	PRIORITY_QUEUE_ON_AVL_TREE<int> a;

	EXPECT_EQ(1, a.isEmpty());
}

TEST(PRIORITY_QUEUE_ON_AVL_TREE, can_get_size_queue){
	PRIORITY_QUEUE_ON_AVL_TREE<int> a;

	ASSERT_NO_THROW(a.getSize());
}

TEST(PRIORITY_QUEUE_ON_AVL_TREE, getSize_works_properly){
	PRIORITY_QUEUE_ON_AVL_TREE<int> a;

	EXPECT_EQ(0, a.getSize());
}

TEST(PRIORITY_QUEUE_ON_AVL_TREE, can_push_key){
	PRIORITY_QUEUE_ON_AVL_TREE<int> a;

	ASSERT_NO_THROW(a.push(1));
}

TEST(PRIORITY_QUEUE_ON_AVL_TREE, push_increases_size){
	PRIORITY_QUEUE_ON_AVL_TREE<int> a;
	int tmp = a.getSize();
	a.push(1);

	EXPECT_EQ(tmp + 1, a.getSize());
}

TEST(PRIORITY_QUEUE_ON_AVL_TREE, can_pop_elem){
	PRIORITY_QUEUE_ON_AVL_TREE<int> a;
	a.push(1);
	a.push(2);

	ASSERT_NO_THROW(a.pop());
}

TEST(PRIORITY_QUEUE_ON_AVL_TREE, throws_when_pop_from_empty){
	PRIORITY_QUEUE_ON_AVL_TREE<int> a;

	ASSERT_ANY_THROW(a.pop());
}

TEST(PRIORITY_QUEUE_ON_AVL_TREE, pop_decreases_size){
	PRIORITY_QUEUE_ON_AVL_TREE<int> a;
	a.push(1);
	a.push(2);
	int tmp = a.getSize();
	a.pop();

	EXPECT_EQ(tmp - 1, a.getSize());
}

TEST(PRIORITY_QUEUE_ON_AVL_TREE, can_get_back_elem){
	PRIORITY_QUEUE_ON_AVL_TREE<int> a;
	a.push(1);
	a.push(2);

	ASSERT_NO_THROW(a.back());
}

TEST(PRIORITY_QUEUE_ON_AVL_TREE, throws_when_back_from_empty){
	PRIORITY_QUEUE_ON_AVL_TREE<int> a;

	ASSERT_ANY_THROW(a.back());
}

TEST(PRIORITY_QUEUE_ON_AVL_TREE, back_dont_decrease_size){
	PRIORITY_QUEUE_ON_AVL_TREE<int> a;
	a.push(1);
	a.push(2);
	int tmp = a.getSize();
	a.back();

	EXPECT_EQ(tmp, a.getSize());
}

TEST(PRIORITY_QUEUE_ON_AVL_TREE, back_returns_elem_with_max_priority){
	PRIORITY_QUEUE_ON_AVL_TREE<int> a;
	for (int i = 10; i > -1; i--){
		a.push(i);
	}

	EXPECT_EQ(0, a.back());
}

TEST(PRIORITY_QUEUE_ON_AVL_TREE, can_copy_queue){
	PRIORITY_QUEUE_ON_AVL_TREE<int> a;
	a.push(3);

	ASSERT_NO_THROW(PRIORITY_QUEUE_ON_AVL_TREE<int> b(a));
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, can_create_queue){
	PRIORITY_QUEUE<int>* a;

	ASSERT_NO_THROW(a = new PRIORITY_QUEUE_ON_SORT_TABLE<int>(2));
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, created_queue_is_empty){
	PRIORITY_QUEUE_ON_SORT_TABLE<int> a(2);

	EXPECT_EQ(1, a.isEmpty());
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, can_get_size_queue){
	PRIORITY_QUEUE_ON_SORT_TABLE<int> a(2);

	ASSERT_NO_THROW(a.getSize());
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, getSize_works_properly){
	PRIORITY_QUEUE_ON_SORT_TABLE<int> a(2);

	EXPECT_EQ(0, a.getSize());
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, can_push_key){
	PRIORITY_QUEUE_ON_SORT_TABLE<int> a(2);

	ASSERT_NO_THROW(a.push(1));
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, push_increases_size){
	PRIORITY_QUEUE_ON_SORT_TABLE<int> a(2);
	int tmp = a.getSize();
	a.push(1);

	EXPECT_EQ(tmp + 1, a.getSize());
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, can_pop_elem){
	PRIORITY_QUEUE_ON_SORT_TABLE<int> a(5);
	a.push(1);
	a.push(2);

	ASSERT_NO_THROW(a.pop());
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, throws_when_pop_from_empty){
	PRIORITY_QUEUE_ON_SORT_TABLE<int> a(1);

	ASSERT_ANY_THROW(a.pop());
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, pop_decreases_size){
	PRIORITY_QUEUE_ON_SORT_TABLE<int> a(5);
	a.push(1);
	a.push(2);
	int tmp = a.getSize();
	a.pop();

	EXPECT_EQ(tmp - 1, a.getSize());
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, can_get_back_elem){
	PRIORITY_QUEUE_ON_SORT_TABLE<int> a(5);
	a.push(1);
	a.push(2);

	ASSERT_NO_THROW(a.back());
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, throws_when_back_from_empty){
	PRIORITY_QUEUE_ON_SORT_TABLE<int> a(2);

	ASSERT_ANY_THROW(a.back());
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, back_dont_decrease_size){
	PRIORITY_QUEUE_ON_SORT_TABLE<int> a(5);
	a.push(1);
	a.push(2);
	int tmp = a.getSize();
	a.back();

	EXPECT_EQ(tmp, a.getSize());
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, back_returns_elem_with_max_priority){
	PRIORITY_QUEUE_ON_SORT_TABLE<int> a(12);
	for (int i = 10; i > -1; i--){
		a.push(i);
	}

	EXPECT_EQ(0, a.back());
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, can_copy_queue){
	PRIORITY_QUEUE_ON_SORT_TABLE<int> a(2);
	a.push(3);

	ASSERT_NO_THROW(PRIORITY_QUEUE_ON_SORT_TABLE<int> b(a));
}

TEST(PRIORITY_QUEUE_ON_SORT_TABLE, copied_queue_is_equal_to_source_one){
	PRIORITY_QUEUE_ON_SORT_TABLE<int> a(2);
	for (int i = 0; i < 10; i++){
		a.push(i);
	}
	SORT_TABLE<int> t1 = a.getTable();
	PRIORITY_QUEUE_ON_SORT_TABLE<int> b(a);
	SORT_TABLE<int> t2 = b.getTable();
	t1.reset();
	t2.reset();
	for(size_t i = 0; i < 10; i++){
	EXPECT_EQ(t1.getCurrentRecord()->getKey(), t2.getCurrentRecord()->getKey());
	t1.goNext();
	t2.goNext();
	}
}