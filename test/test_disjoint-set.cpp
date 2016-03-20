#include <gtest.h>
#include "disjoint-set.h"

TEST(DisjointSet, can_create_disjoint_set) {
    ASSERT_NO_THROW(DISJOINT_SET a(3));
}

TEST(DisjointSet, throws_when_create_disjoint_set_vith_negative_size) {
    ASSERT_ANY_THROW(DISJOINT_SET a(-1));
}

TEST(DisjointSet, can_get_U) {
    DISJOINT_SET a(10);
    ASSERT_NO_THROW(a.getUniversalSet());
}

TEST(DisjointSet, created_elem_is_empty) {
    DISJOINT_SET a(10);
    TVector b = a.getUniversalSet();
    int i = 0;
    for (i; i < b.GetSize(); i++)
        if (b[i] != -1) break;

    EXPECT_EQ(10, i);
}

TEST(DisjointSet, can_get_number_of_sets) {
    DISJOINT_SET a(10);
    ASSERT_NO_THROW(a.getNumberOfSets());
    EXPECT_EQ(0, a.getNumberOfSets());
}

TEST(DisjointSet, can_create_set) {
    DISJOINT_SET a(10);
    ASSERT_NO_THROW(a.createSet(2));
}

TEST(DisjointSet, throws_when_create_set_with_incorrect_argument) {
    DISJOINT_SET a(10);
    ASSERT_ANY_THROW(a.createSet(-1));
    ASSERT_ANY_THROW(a.createSet(10));
}

TEST(DisjointSet, can_copy_elem) {
    DISJOINT_SET a(10);
    a.createSet(7);
    a.createSet(4);
    a.createSet(0);
    ASSERT_NO_THROW(DISJOINT_SET b(a));
}

TEST(DisjointSet, copied_elem_is_equal_to_source_one) {
    DISJOINT_SET a(10);
    a.createSet(7);
    a.createSet(4);
    a.createSet(0);
    DISJOINT_SET b(a);
    EXPECT_EQ(a.getUniversalSet(), b.getUniversalSet());
    EXPECT_EQ(a.getNumberOfSets(), a.getNumberOfSets());
}

TEST(DisjointSet, createSet_increases_number_of_set) {
    DISJOINT_SET a(10);
    a.createSet(7);
    a.createSet(4);
    a.createSet(0);
    int tmp = a.getNumberOfSets();
    a.createSet(1);
    EXPECT_EQ(tmp + 1, a.getNumberOfSets());
}

TEST(DisjointSet, throws_when_created_existing_set) {
    DISJOINT_SET a(10);
    a.createSet(7);
    a.createSet(4);
    a.createSet(0);

    ASSERT_ANY_THROW(a.createSet(0));
}

TEST(DisjointSet, can_unite_sets) {
    DISJOINT_SET a(10);
    a.createSet(7);
    a.createSet(4);
    a.createSet(0);
    ASSERT_NO_THROW(a.uniteSets(0, 4));
}

TEST(DisjointSet, throws_when_unite_sets_with_invalid_arguments) {
    DISJOINT_SET a(10);
    a.createSet(7);
    a.createSet(4);
    a.createSet(0);

    ASSERT_ANY_THROW(a.uniteSets(-1, 0));
    ASSERT_ANY_THROW(a.uniteSets(10, 0));
    ASSERT_ANY_THROW(a.uniteSets(0, 10));
    ASSERT_ANY_THROW(a.uniteSets(0, -1));
}

TEST(DisjointSet, throws_when_unite_existing_and_non_existing_sets) {
    DISJOINT_SET a(10);
    a.createSet(7);
    a.createSet(4);
    a.createSet(0);
    ASSERT_ANY_THROW(a.uniteSets(1, 0));
    ASSERT_ANY_THROW(a.uniteSets(0, 1));
}

TEST(DisjointSet, throws_when_one_of_arguments_of_uniteSets_is_not_root) {
    DISJOINT_SET a(10);
    a.createSet(7);
    a.createSet(4);
    a.createSet(0);
    a.uniteSets(0, 7);
    ASSERT_ANY_THROW(a.uniteSets(7, 4));
    ASSERT_ANY_THROW(a.uniteSets(4, 7));
}

TEST(DisjointSet, can_find_root_of_set) {
    DISJOINT_SET a(10);
    a.createSet(7);
    a.createSet(4);
    a.createSet(0);
    a.uniteSets(0, 7);
    ASSERT_NO_THROW(a.findSet(7));
    EXPECT_EQ(0, a.findSet(7));
    EXPECT_EQ(-1, a.findSet(1));
}

TEST(DisjointSet, throws_when_findSet_has_incorrect_argument) {
    DISJOINT_SET a(10);
    a.createSet(7);
    a.createSet(4);
    a.createSet(0);
    a.uniteSets(0, 7);
    ASSERT_ANY_THROW(a.findSet(-1));
    ASSERT_ANY_THROW(a.findSet(10));
}

TEST(DisjointSet, can_get_set) {
    DISJOINT_SET a(3);
    a.createSet(2);
    a.createSet(1);
    a.createSet(0);
    a.uniteSets(0, 2);
    TVector b;
    ASSERT_NO_THROW(b = a.getSet(0));
    TVector c(2);
    c[0] = 0; c[1] = 2;
    EXPECT_EQ(c, b);
}

TEST(DisjointSet, throws_when_get_non_existing_set) {
    DISJOINT_SET a(10);
    a.createSet(7);
    a.createSet(4);
    a.createSet(0);
    a.uniteSets(0, 7);
    TVector b;
    ASSERT_ANY_THROW(b = a.getSet(1));
}

TEST(DisjointSet, throws_when_argument_of_getSet_is_not_root) {
    DISJOINT_SET a(10);
    a.createSet(7);
    a.createSet(4);
    a.createSet(0);
    a.uniteSets(0, 7);
    TVector b;
    ASSERT_ANY_THROW(b = a.getSet(7));
}

TEST(DisjointSet, throws_when_get_set_with_incorrect_argument) {
    DISJOINT_SET a(10);
    a.createSet(7);
    a.createSet(4);
    a.createSet(0);
    a.uniteSets(0, 7);
    TVector b;
    ASSERT_ANY_THROW(b = a.getSet(-1));
    ASSERT_ANY_THROW(b = a.getSet(10));
}
