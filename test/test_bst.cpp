#include <gtest.h>
#include "bst.hpp"
#include "avl-tree.hpp"

TEST(BINARY_SEARCH_TREE, can_create_binary_tree) {
	ASSERT_NO_THROW(BST<int> a);
}

TEST(BINARY_SEARCH_TREE, created_tree_is_empty) {
	BST<int> a;
	EXPECT_EQ(0, a.getSize());
}

TEST(BINARY_SEARCH_TREE, can_insert_key_to_tree) {
	BST<int> a;
	ASSERT_NO_THROW(a.insert(3));
}

TEST(BINARY_SEARCH_TREE, insertion_increases_size_tree) {
	BST<int> a;
	size_t tmp = a.getSize();
	a.insert(3);
	EXPECT_EQ(tmp + 1, a.getSize());
}

TEST(BINARY_SEARCH_TREE, can_copy_tree) {
	BST<int> a;
	a.insert(7);
	a.insert(2);
	a.insert(3);
	a.insert(8);
	a.insert(5);
	a.insert(15);
	a.insert(25);
	a.insert(10);
	ASSERT_NO_THROW(BST<int> b(a));
}

TEST(BINARY_SEARCH_TREE, copied_tree_is_equal_to_source_one) {
	BST<int> a;
	a.insert(7);
	a.insert(2);
	a.insert(3);
	a.insert(8);
	a.insert(5);
	a.insert(15);
	a.insert(25);
	a.insert(10);
	BST<int> b(a);
	vector<NODE<int>* > exp = a.recPostOrder(),
		actual = b.recPostOrder();

	for (size_t i = 0; i < a.getSize(); i++) {
		EXPECT_EQ(exp[i]->data_, actual[i]->data_);
	}

}

TEST(BINARY_SEARCH_TREE, copied_tree_has_its_own_memory) {
	BST<int> a;
	a.insert(7);
	a.insert(2);
	a.insert(3);
	a.insert(8);
	a.insert(5);
	a.insert(15);
	a.insert(25);
	a.insert(10);
	BST<int> b(a);
	vector<NODE<int>* > exp = a.recPostOrder(),
		actual = b.recPostOrder();

	for (size_t i = 0; i < a.getSize(); i++) {
		EXPECT_NE(exp[i], actual[i]);
	}
}

TEST(BINARY_SEARCH_TREE, can_erase_node_from_tree) {
	BST<int> a;
	a.insert(7);
	a.insert(2);
	a.insert(3);
	a.insert(8);
	a.insert(5);
	a.insert(15);
	a.insert(25);
	a.insert(10);
	ASSERT_NO_THROW(a.erase(5));
	ASSERT_NO_THROW(a.erase(7));
	ASSERT_NO_THROW(a.erase(15));
}

TEST(BINARY_SEARCH_TREE, erasing_decreases_size_tree) {
	BST<int> a;
	a.insert(7);
	a.insert(2);
	a.insert(3);
	a.insert(8);
	a.insert(5);
	a.insert(15);
	a.insert(25);
	a.insert(10);
	size_t tmp = a.getSize();
	a.erase(7);
	EXPECT_EQ(tmp - 1, a.getSize());
}

TEST(BINARY_SEARCH_TREE, can_find_node) {
	BST<int> a;
	a.insert(7);
	a.insert(2);
	a.insert(3);
	a.insert(8);
	a.insert(5);
	a.insert(15);
	a.insert(25);
	a.insert(10);
	ASSERT_NO_THROW(a.find(8));
	EXPECT_EQ(8, a.find(8)->data_);
}

TEST(BINARY_SEARCH_TREE, throws_when_find_works_with_argument_is_equal_to_NULL) {
	BST<int> a;
	ASSERT_ANY_THROW(a.find(1));
}

TEST(BINARY_SEARCH_TREE, can_find_node_with_min_key) {
	BST<int> a;
	a.insert(7);
	a.insert(2);
	a.insert(3);
	a.insert(8);
	a.insert(5);
	a.insert(15);
	a.insert(25);
	a.insert(10);
	ASSERT_NO_THROW(a.findMin());
	EXPECT_EQ(2, a.findMin()->data_);
}

TEST(BINARY_SEARCH_TREE, throws_when_findMin_works_with_argument_is_equal_to_NULL) {
	BST<int> a;
	ASSERT_ANY_THROW(a.findMin());
}

TEST(BINARY_SEARCH_TREE, can_find_node_with_max_key) {
	BST<int> a;
	a.insert(7);
	a.insert(2);
	a.insert(3);
	a.insert(8);
	a.insert(5);
	a.insert(15);
	a.insert(25);
	a.insert(10);
	ASSERT_NO_THROW(a.findMax());
	EXPECT_EQ(25, a.findMax()->data_);
}

TEST(BINARY_SEARCH_TREE, throws_when_findMax_works_with_argument_is_equal_to_NULL) {
	BST<int> a;
	ASSERT_ANY_THROW(a.findMax());
}

TEST(BINARY_SEARCH_TREE, can_find_previously_node) {
	BST<int> a;
	a.insert(7);
	a.insert(2);
	a.insert(3);
	a.insert(8);
	a.insert(5);
	a.insert(15);
	a.insert(25);
	a.insert(10);
	ASSERT_NO_THROW(a.findPrev(a.find(7)));
	EXPECT_EQ(5, a.findPrev(a.find(7))->data_);

	ASSERT_NO_THROW(a.findPrev(a.find(10)));
	EXPECT_EQ(8, a.findPrev(a.find(10))->data_);

	ASSERT_NO_THROW(a.findPrev(a.find(5)));
	EXPECT_EQ(3, a.findPrev(a.find(5))->data_);
}

TEST(BINARY_SEARCH_TREE, throws_when_findPrev_works_with_argument_is_equal_to_NULL) {
	BST<int> a;
	ASSERT_ANY_THROW(a.findPrev(NULL));
}

TEST(BINARY_SEARCH_TREE, throws_when_previously_node_does_not_exist) {
	BST<int> a;
	a.insert(7);
	a.insert(2);
	a.insert(3);
	a.insert(8);
	a.insert(5);
	a.insert(15);
	a.insert(25);
	a.insert(10);
	ASSERT_ANY_THROW(a.findPrev(a.find(2)));
}

TEST(BINARY_SEARCH_TREE, can_find_next_node) {
	BST<int> a;
	a.insert(7);
	a.insert(2);
	a.insert(3);
	a.insert(8);
	a.insert(5);
	a.insert(15);
	a.insert(25);
	a.insert(10);
	ASSERT_NO_THROW(a.findNext(a.find(7)));
	EXPECT_EQ(8, a.findNext(a.find(7))->data_);

	ASSERT_NO_THROW(a.findNext(a.find(5)));
	EXPECT_EQ(7, a.findNext(a.find(5))->data_);

	ASSERT_NO_THROW(a.findNext(a.find(10)));
	EXPECT_EQ(15, a.findNext(a.find(10))->data_);
}

TEST(BINARY_SEARCH_TREE, throws_when_findNext_works_with_argument_is_equal_to_NULL) {
	BST<int> a;
	ASSERT_ANY_THROW(a.findNext(NULL));
}

TEST(BINARY_SEARCH_TREE, throws_when_next_node_does_not_exist) {
	BST<int> a;
	a.insert(7);
	a.insert(2);
	a.insert(3);
	a.insert(8);
	a.insert(5);
	a.insert(15);
	a.insert(25);
	a.insert(10);
	ASSERT_ANY_THROW(a.findNext(a.find(25)));
}

//==========================================================

TEST(AVL_TREE, can_create_tree) {
	ASSERT_NO_THROW(AVL_TREE<int> a);
}

TEST(AVL_TREE, created_tree_is_empty) {
	AVL_TREE<int> a;
	EXPECT_EQ(0, a.getSize());
}

TEST(AVL_TREE, can_insert_key_to_tree) {
	AVL_TREE<int> a;
	ASSERT_NO_THROW(a.insert(3));
}

TEST(AVL_TREE, insertion_increases_size_tree) {
	AVL_TREE<int> a;
	size_t tmp = a.getSize();
	a.insert(3);
	EXPECT_EQ(tmp + 1, a.getSize());
}

TEST(AVL_TREE, can_erase_node_from_tree) {
	AVL_TREE<int> a;
	a.insert(7);
	a.insert(2);
	a.insert(3);
	a.insert(8);
	a.insert(5);
	a.insert(15);
	a.insert(25);
	a.insert(10);
	ASSERT_NO_THROW(a.erase(5));
	ASSERT_NO_THROW(a.erase(7));
	ASSERT_NO_THROW(a.erase(15));
}

TEST(AVL_TREE, erasing_decreases_size_tree) {
	AVL_TREE<int> a;
	a.insert(7);
	a.insert(2);
	a.insert(3);
	a.insert(8);
	a.insert(5);
	a.insert(15);
	a.insert(25);
	a.insert(10);
	size_t tmp = a.getSize();
	a.erase(7);
	EXPECT_EQ(tmp - 1, a.getSize());
}