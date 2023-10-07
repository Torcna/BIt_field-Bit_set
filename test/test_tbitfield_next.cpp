#include <gtest.h>
#include "tbitfield.h"

TEST(TBitField, can_set_last_bit_1)
{
    const size_t num_el = 1;
    const size_t n = sizeof(myuint) * 8 * num_el;
    TBitField field(n);
    ASSERT_EQ(field.getNumBytes(), sizeof(myuint) * num_el);
    ASSERT_NO_THROW(field.setBit(n - 1));
    ASSERT_EQ(field.getBit(n - 1), true);
}

TEST(TBitField, can_set_last_bit_2)
{
    const size_t num_el = 15;
    const size_t n = sizeof(myuint) * 8 * num_el;
    TBitField field(n);
    ASSERT_EQ(field.getNumBytes(), sizeof(myuint) * num_el);
    ASSERT_NO_THROW(field.setBit(n - 1));
    ASSERT_EQ(field.getBit(n - 1), true);
}

TEST(TBitField, can_set_last_bit_3)
{
    const size_t num_el = 15;
    const size_t n = sizeof(myuint) * 8 * num_el;
    TBitField field1(n);
    ASSERT_NO_THROW(field1.setBit(n - 1));

    TBitField field2(field1);
    ASSERT_EQ(field2.getNumBytes(), sizeof(myuint) * num_el);
    ASSERT_NO_THROW(field2.setBit(n - 1));
    ASSERT_EQ(field2.getBit(n - 1), true);
}

TEST(TBitField, can_not_set_bit_after_last_1)
{
    const size_t num_el = 1;
    const size_t n = sizeof(myuint) * num_el;
    TBitField field(n);
    ASSERT_ANY_THROW(field.setBit(n));
}

TEST(TBitField, can_not_set_bit_after_last_2)
{
    const size_t num_el = 21;
    const size_t n = sizeof(myuint) * 8 * num_el;
    TBitField field(n);
    ASSERT_ANY_THROW(field.setBit(n));
}

TEST(TBitField, can_set_half_bits)
{
    const size_t num_el = 1;
    const size_t n = sizeof(myuint) * 8 * num_el;
    TBitField field(n);
    for (size_t i = 0; i < field.getLength() / 2; i++)
        field.setBit(i);
    for (size_t i = 0; i < field.getLength() / 2; i++)
        ASSERT_EQ(field.getBit(i), true);
    for (size_t i = field.getLength() / 2; i < field.getLength(); i++)
        ASSERT_EQ(field.getBit(i), false);
}