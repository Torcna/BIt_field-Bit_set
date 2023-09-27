#include <gtest.h>
#include "tset.h"
#include <vector>

TEST(TSet, can_get_max_power_set)
{
    std::vector<int> s();
    const size_t size = 5;
    TSet set(size);

    EXPECT_EQ(size, set.getMaxPower());
}

TEST(TSet, can_insert_non_existing_element)
{
    const size_t size = 5;
    const uint k = 3;
    TSet set(size);
    set.insElem(k);

    EXPECT_NE(set.isMember(k), false);
}

TEST(TSet, can_insert_existing_element)
{
    const size_t size = 5;
    const uint k = 3;
    TSet set(size);
    set.insElem(k);
    set.insElem(k);

    EXPECT_NE(set.isMember(k), false);
}

TEST(TSet, can_delete_non_existing_element)
{
    const size_t size = 5;
    const uint k = 3;
  TSet set(size);
  set.delElem(k);

  EXPECT_EQ(set.isMember(k), false);
}

TEST(TSet, can_delete_existing_element)
{
    const size_t size = 5;
    const uint k = 3;
    TSet set(size);

    set.insElem(k);
    EXPECT_GT(set.isMember(k), false);

    set.delElem(k);
    EXPECT_EQ(set.isMember(k), false);
}

TEST(TSet, compare_two_sets_of_non_equal_sizes)
{
    const size_t size1 = 4, size2 = 6;
    TSet set1(size1), set2(size2);

    EXPECT_EQ(1, set1 != set2);
}

TEST(TSet, compare_two_equal_sets)
{
    const size_t size = 4;
    TSet set1(size), set2(size);
    // set1 = set2 = {1, 3}
    set1.insElem(1);
    set1.insElem(3);
    set2.insElem(1);
    set2.insElem(3);

    EXPECT_EQ(set1, set2);
}

TEST(TSet, compare_two_non_equal_sets)
{
    const size_t size = 4;
    TSet set1(size), set2(size);
    // set1 = {1, 3}
    set1.insElem(1);
    set1.insElem(3);
    // set2 = {1, 2}
    set2.insElem(1);
    set2.insElem(2);

    EXPECT_EQ(1, set1 != set2);
}

TEST(TSet, can_assign_set_of_equal_size)
{
    const size_t size = 4;
    TSet set1(size), set2(size);
    // set1 = {1, 3}
    set1.insElem(1);
    set1.insElem(3);
    set2 = set1;

    EXPECT_EQ(set1, set2);
}

TEST(TSet, can_assign_set_of_greater_size)
{
    const size_t size1 = 4, size2 = 6;
    TSet set1(size1), set2(size2);
    // set1 = {1, 3}
    set1.insElem(1);
    set1.insElem(3);
    set2 = set1;

    EXPECT_EQ(set1, set2);
}

TEST(TSet, can_assign_set_of_less_size)
{
    const size_t size1 = 6, size2 = 4;
    TSet set1(size1), set2(size2);
    // set1 = {1, 3, 5}
    set1.insElem(1);
    set1.insElem(3);
    set1.insElem(5);
    set2 = set1;

    EXPECT_EQ(set1, set2);
}

TEST(TSet, can_insert_non_existing_element_using_plus_operator)
{
    const size_t size = 4;
    const uint k = 3;
    TSet set(size), updatedSet(size);
    set.insElem(0);
    set.insElem(2);
    updatedSet = set + k;

    EXPECT_NE(false, updatedSet.isMember(k));
}

TEST(TSet, throws_when_insert_non_existing_element_out_of_range_using_plus_operator)
{
    const size_t size = 4;
    const uint k = 6;
    TSet set(size), updatedSet(size);
    set.insElem(0);
    set.insElem(2);

    ASSERT_ANY_THROW(updatedSet = set + k);
}

TEST(TSet, can_insert_existing_element_using_plus_operator)
{
    const size_t size = 4;
    const uint k = 3;
    TSet set(size), updatedSet(size);
    set.insElem(0);
    set.insElem(k);
    updatedSet = set + k;

    EXPECT_NE(false, set.isMember(k));
}

TEST(TSet, check_size_of_the_combination_of_two_sets_of_equal_size)
{
    const size_t size = 5;
    TSet set1(size), set2(size), set3(size);
    // set1 = {1, 2, 4}
    set1.insElem(1);
    set1.insElem(2);
    set1.insElem(4);
    // set2 = {0, 1, 2}
    set2.insElem(0);
    set2.insElem(1);
    set2.insElem(2);
    set3 = set1 + set2;

    EXPECT_EQ(size, set3.getMaxPower());
}

TEST(TSet, can_combine_two_sets_of_equal_size)
{
    const size_t size = 5;
    TSet set1(size), set2(size), set3(size), expSet(size);
    // set1 = {1, 2, 4}
    set1.insElem(1);
    set1.insElem(2);
    set1.insElem(4);
    // set2 = {0, 1, 2}
    set2.insElem(0);
    set2.insElem(1);
    set2.insElem(2);
    set3 = set1 + set2;
    // expSet = {0, 1, 2, 4}
    expSet.insElem(0);
    expSet.insElem(1);
    expSet.insElem(2);
    expSet.insElem(4);

    EXPECT_EQ(expSet, set3);
}

TEST(TSet, check_size_changes_of_the_combination_of_two_sets_of_non_equal_size)
{
    const size_t size1 = 5, size2 = 7;
    TSet set1(size1), set2(size2), set3(size1);
    // set1 = {1, 2, 4}
    set1.insElem(1);
    set1.insElem(2);
    set1.insElem(4);
    // set2 = {0, 1, 2}
    set2.insElem(0);
    set2.insElem(1);
    set2.insElem(2);
    set3 = set1 + set2;

    EXPECT_EQ(size2, set3.getMaxPower());
}

TEST(TSet, can_combine_two_sets_of_non_equal_size)
{
    const size_t size1 = 5, size2 = 7;
    TSet set1(size1), set2(size2), set3(size1), expSet(size2);
    // set1 = {1, 2, 4}
    set1.insElem(1);
    set1.insElem(2);
    set1.insElem(4);
    // set2 = {0, 1, 2, 6}
    set2.insElem(0);
    set2.insElem(1);
    set2.insElem(2);
    set2.insElem(6);
    set3 = set1 + set2;
    // expSet = {0, 1, 2, 4, 6}
    expSet.insElem(0);
    expSet.insElem(1);
    expSet.insElem(2);
    expSet.insElem(4);
    expSet.insElem(6);

    EXPECT_EQ(expSet, set3);
}

TEST(TSet, can_intersect_two_sets_of_equal_size)
{
    const size_t size = 5;
    TSet set1(size), set2(size), set3(size), expSet(size);
    // set1 = {1, 2, 4}
    set1.insElem(1);
    set1.insElem(2);
    set1.insElem(4);
    // set2 = {0, 1, 2}
    set2.insElem(0);
    set2.insElem(1);
    set2.insElem(2);
    set3 = set1 * set2;
    // expSet = {1, 2}
    expSet.insElem(1);
    expSet.insElem(2);

    EXPECT_EQ(expSet, set3);
}

TEST(TSet, can_intersect_two_sets_of_non_equal_size)
{
    const size_t size1 = 5, size2 = 7;
    TSet set1(size1), set2(size2), set3(size1), expSet(size2);
    // set1 = {1, 2, 4}
    set1.insElem(1);
    set1.insElem(2);
    set1.insElem(4);
    // set2 = {0, 1, 2, 4, 6}
    set2.insElem(0);
    set2.insElem(1);
    set2.insElem(2);
    set2.insElem(4);
    set2.insElem(6);
    set3 = set1 * set2;
    // expSet = {1, 2, 4}
    expSet.insElem(1);
    expSet.insElem(2);
    expSet.insElem(4);

    EXPECT_EQ(expSet, set3);
}

TEST(TSet, check_negation_operator)
{
    const size_t size = 4;
    TSet set(size), set1(size), expSet(size);
    // set1 = {1, 3}
    set.insElem(1);
    set.insElem(3);
    set1 = ~set;
    // expSet = {0, 2}
    expSet.insElem(0);
    expSet.insElem(2);

    EXPECT_EQ(expSet, set1);
}

TEST(TSet, testCoutInsClearPlusMinus)
{
    const size_t size = 13;
    TSet set(size), set1(size), expSet(size);
    // set1 = {1, 3}
    set.insElem(1);
    set.delElem(1);
    set.delElem(1);
    set1 = set1 + 1 + 3 + 5 + 12;
    set1 = set1 - 1 - 3 - 5 - 12;
    set1 = set1 - 1;
    EXPECT_EQ(expSet, set1 + set + set1);
}
