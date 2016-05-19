#include <gtest.h>
#include "tables.hpp"

TEST(SCAN_TABLE, can_create_table) {
	ASSERT_NO_THROW(SCAN_TABLE<int> a(5));
}

TEST(SCAN_TABLE, created_table_is_empty) {
	SCAN_TABLE<int> a(5);
	EXPECT_EQ(1, a.isEmpty());
}

TEST(SCAN_TABLE, can_insert_record_to_table) {
	SCAN_TABLE<int> a(5);
	ASSERT_NO_THROW(a.insert(1));
}

TEST(SCAN_TABLE, can_erase_record_from_table) {
	SCAN_TABLE<int> a(5);
	a.insert(1);
	ASSERT_NO_THROW(a.erase(1));
}

TEST(SCAN_TABLE, insert_increase_size_of_table) {
	SCAN_TABLE<int> a(5);
	size_t exp = a.getCount() + 1;
	a.insert(1);
	EXPECT_EQ(exp, a.getCount());
}

TEST(SCAN_TABLE, erase_decrease_size_of_table) {
	SCAN_TABLE<int> a(5);
	a.insert(1);
	size_t exp = a.getCount() - 1;
	a.erase(1);
	EXPECT_EQ(exp, a.getCount());
}

TEST(SCAN_TABLE, can_find_record) {
	SCAN_TABLE<int> a(5);
	a.insert(1);
	a.insert(2);
	a.insert(3);
	ASSERT_NO_THROW(a.find(2));
	EXPECT_EQ(2, a.find(2)->getKey());
}

TEST(SCAN_TABLE, find_returns_NULL_if_error_404) {
	SCAN_TABLE<int> a(5);
	a.insert(1);
	a.insert(2);
	a.insert(3);
	EXPECT_EQ(NULL, a.find(4));
}

TEST(SCAN_TABLE, cant_insert_record_to_table_when_table_is_full) {
	SCAN_TABLE<int> a(5);
	a.insert(1);
	a.insert(2);
	a.insert(3);
	a.insert(4);
	a.insert(6);
	ASSERT_ANY_THROW(a.insert(7));
}

TEST(SCAN_TABLE, can_get_current_record) {
	SCAN_TABLE<int> a(5);
	a.insert(1);
	a.insert(2);
	a.insert(3);
	a.insert(4);
	a.insert(6);
	a.reset();
	TAB_RECORD<int>* tmp;
	ASSERT_NO_THROW(tmp = a.getCurrentRecord());
	EXPECT_EQ(1, tmp->getKey());
}

TEST(SCAN_TABLE, can_erase_current_record) {
	SCAN_TABLE<int> a(5);
	a.insert(1);
	a.insert(2);
	a.insert(3);
	a.insert(4);
	a.insert(6);
	a.reset();
	size_t tmp = a.getCount();
	ASSERT_NO_THROW(a.eraseCurrentRecord());
	EXPECT_EQ(tmp - 1, a.getCount());
	EXPECT_EQ(NULL, a.find(1));
}

//=============================================================

TEST(SORT_TABLE, can_create_table) {
	SORT_TABLE<int> a(1);
	ASSERT_NO_THROW(a.getCount());
}

TEST(SORT_TABLE, created_table_is_empty) {
	SORT_TABLE<int> a(5);
	EXPECT_EQ(1, a.isEmpty());
}

TEST(SORT_TABLE, can_insert_record_to_table) {
	SORT_TABLE<int> a(5);
	ASSERT_NO_THROW(a.insert(1));
}

TEST(SORT_TABLE, can_erase_record_from_table) {
	SORT_TABLE<int> a(5);
	a.insert(1);
	ASSERT_NO_THROW(a.erase(1));
}

TEST(SORT_TABLE, insert_increase_size_of_table) {
	SORT_TABLE<int> a(5);
	size_t exp = a.getCount() + 1;
	a.insert(1);
	EXPECT_EQ(exp, a.getCount());
}

TEST(SORT_TABLE, erase_decrease_size_of_table) {
	SORT_TABLE<int> a(5);
	a.insert(1);
	size_t exp = a.getCount() - 1;
	a.erase(1);
	EXPECT_EQ(exp, a.getCount());
}

TEST(SORT_TABLE, can_find_record) {
	SORT_TABLE<int> a(5);
	a.insert(1);
	a.insert(2);
	a.insert(3);
	ASSERT_NO_THROW(a.find(2));
	EXPECT_EQ(2, a.find(2)->getKey());
}

TEST(SORT_TABLE, find_returns_NULL_if_error_404) {
	SORT_TABLE<int> a(5);
	a.insert(1);
	a.insert(2);
	a.insert(3);
	EXPECT_EQ(NULL, a.find(4));
}

TEST(SORT_TABLE, cant_insert_record_to_table_when_table_is_full) {
	SORT_TABLE<int> a(5);
	a.insert(1);
	a.insert(2);
	a.insert(3);
	a.insert(4);
	a.insert(6);
	ASSERT_ANY_THROW(a.insert(7));
}


