#include "tvector.hpp"

#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
#include <gtest.h>
#endif

TEST(TVector, can_create_vector_with_positive_length){
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, throws_when_create_vector_with_negative_length){
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, can_create_copied_vector){
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one){
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(a);
    EXPECT_EQ(a, b);
}

TEST(TVector, copied_vector_has_its_own_memory){
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(a);
    EXPECT_NE(&a[0], &b[0]);
}

TEST(TVector, can_get_size){
  TVector<int> v(4);

  EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_element){
  TVector<int> a(4);
  for (int i = 0; i < a.GetSize(); i++)
      a[i] = 0;
  a[3] = 7;
  ASSERT_NO_THROW(a[0]);
}

TEST(TVector, can_set_element){
    TVector<int> a(4);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    ASSERT_NO_THROW(a[0] = 1);
}

TEST(TVector, throws_when_set_element_with_negative_index){
    TVector<int> a(5);
    ASSERT_ANY_THROW(a[-1] = 1);
}

TEST(TVector, throws_when_set_element_with_too_large_index){
    TVector<int> a(5);
    ASSERT_ANY_THROW(a[7] = 1);
}

TEST(TVector, can_assign_vector_to_itself){
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
  ASSERT_NO_THROW(a = a);
}

TEST(TVector, can_assign_vectors_of_equal_size){
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(5);
    
    ASSERT_NO_THROW(a = b);
}

TEST(TVector, assign_operator_change_vector_size){
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(7);
    for (int i = 0; i < b.GetSize(); i++)
        b[i] = 0;
    int t = a.GetSize();
    a = b;
    EXPECT_NE(t, a.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size){
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(7);
    for (int i = 0; i < b.GetSize(); i++)
        b[i] = 0;

    ASSERT_NO_THROW(a = b);
}

TEST(TVector, assign_operator_change_vector){
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(7);
    for (int i = 0; i < b.GetSize(); i++)
        b[i] = 0;
    b[3] = 7;
    TVector<int> c(a);
    a = b;
    EXPECT_NE(c, a);
}

TEST(TVector, assigned_vector_is_equal_to_source_one){
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    TVector<int> b(7);
    for (int i = 0; i < b.GetSize(); i++)
        b[i] = 0;
    a = b;
    EXPECT_EQ(a, b);
}

TEST(TVector, compare_equal_vectors_return_true){
    TVector<int> a(5);
    TVector<int> b(5);
    for (int i = 0; i < a.GetSize(); i++)
    {
        a[i] = 0;
        b[i] = 0;
    }
    a[3] = 7;
    b[3] = 7;

    EXPECT_EQ(a, b);
}

TEST(TVector, compare_vector_with_itself_return_true){
    TVector<int> a(5);
    for (int i = 0; i < a.GetSize(); i++)
        a[i] = 0;
    a[3] = 7;
    EXPECT_EQ(a, a);
}

TEST(TVector, vectors_with_different_size_are_not_equal){
    TVector<int> a(5);
    TVector<int> b(6);
    for (int i = 0; i < a.GetSize(); i++)
    {
        a[i] = 0;
        b[i] = 0;
    }
    b[5] = 0;
    EXPECT_NE(a, b);
}
