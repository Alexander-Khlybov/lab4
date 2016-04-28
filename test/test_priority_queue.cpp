#include "priority_queue.hpp"
#include <gtest.h>

TEST(PRIORITY_QUEUE, can_create_queue){
	PRIORITY_QUEUE<int>* a;

	ASSERT_NO_THROW(a = new PRIORITY_QUEUE<int>(2));
}

TEST(PRIORITY_QUEUE, created_queue_is_empty){
	PRIORITY_QUEUE<int> a(2);

	EXPECT_EQ(1, a.isEmpty());
}

TEST(PRIORITY_QUEUE, can_get_size_queue){
	PRIORITY_QUEUE<int> a(2);

	ASSERT_NO_THROW(a.getSize());
}

TEST(PRIORITY_QUEUE, getSize_works_properly){
	PRIORITY_QUEUE<int> a(2);

	EXPECT_EQ(0, a.getSize());
}

TEST(PRIORITY_QUEUE, can_push_key){
	PRIORITY_QUEUE<int> a(2);

	ASSERT_NO_THROW(a.push(1));
}

TEST(PRIORITY_QUEUE, push_increases_size){
	PRIORITY_QUEUE<int> a(2);
	int tmp = a.getSize();
	a.push(1);

	EXPECT_EQ(tmp + 1, a.getSize());
}

TEST(PRIORITY_QUEUE, can_pop_elem){
	PRIORITY_QUEUE<int> a(2);
	a.push(1);
	a.push(2);

	ASSERT_NO_THROW(a.pop());
}

TEST(PRIORITY_QUEUE, throws_when_pop_from_empty){
	PRIORITY_QUEUE<int> a(1);

	ASSERT_ANY_THROW(a.pop());
}

TEST(PRIORITY_QUEUE, pop_decreases_size){
	PRIORITY_QUEUE<int> a(2);
	a.push(1);
	a.push(2);
	int tmp = a.getSize();
	a.pop();

	EXPECT_EQ(tmp - 1, a.getSize());
}

TEST(PRIORITY_QUEUE, can_get_back_elem){
	PRIORITY_QUEUE<int> a(2);
	a.push(1);
	a.push(2);

	ASSERT_NO_THROW(a.back());
}

TEST(PRIORITY_QUEUE, throws_when_back_from_empty){
	PRIORITY_QUEUE<int> a(2);

	ASSERT_ANY_THROW(a.back());
}

TEST(PRIORITY_QUEUE, back_dont_decrease_size){
	PRIORITY_QUEUE<int> a(2);
	a.push(1);
	a.push(2);
	int tmp = a.getSize();
	a.back();

	EXPECT_EQ(tmp, a.getSize());
}

TEST(PRIORITY_QUEUE, back_returns_elem_with_max_priority){
	PRIORITY_QUEUE<int> a(2);
	for (int i = 10; i > -1; i--){
		a.push(i);
	}

	EXPECT_EQ(0, a.back());
}

TEST(PRIORITY_QUEUE, push_works_properly){
	PRIORITY_QUEUE<int> a(1);
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

TEST(PRIORITY_QUEUE, can_copy_queue){
	PRIORITY_QUEUE<int> a(2);
	a.push(3);

	ASSERT_NO_THROW(PRIORITY_QUEUE<int> b(a));
}

TEST(PRIORITY_QUEUE, copied_queue_is_equal_to_source_one){
	PRIORITY_QUEUE<int> a(2);
	for (int i = 0; i < 10; i++){
		a.push(i);
	}

	PRIORITY_QUEUE<int> b(a);

	EXPECT_EQ(a, b);
}
