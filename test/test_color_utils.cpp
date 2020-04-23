#include "unity.h"
#include "color_utils.h"

TEST_CASE("color_utils: color16to24", "[Matrix]")
{
    TEST_ASSERT_EQUAL(0, color16to24(0));
    TEST_ASSERT_EQUAL(16777215, color16to24(65535));
    TEST_ASSERT_EQUAL(0xffffff, color16to24(0xffff));

    TEST_ASSERT_EQUAL(0xff0000, color16to24(63488));
    TEST_ASSERT_EQUAL(0xff0000, color16to24(0xf800));
    TEST_ASSERT_EQUAL(0x00ff00, color16to24(2016));
    TEST_ASSERT_EQUAL(0x00ff00, color16to24(0x07e0));
    TEST_ASSERT_EQUAL(0x0000ff, color16to24(31));
    TEST_ASSERT_EQUAL(0x0000ff, color16to24(0x001f));

    TEST_ASSERT_EQUAL(0xffff00, color16to24(65504));
    TEST_ASSERT_EQUAL(0xff00ff, color16to24(63519));
    TEST_ASSERT_EQUAL(0x00ffff, color16to24(2047));
}

TEST_CASE("color_utils: color24to16", "[Matrix]")
{
    // 16 bit == d32 d64 d32

    TEST_ASSERT_EQUAL(0, color24to16(0, 0, 0));
    TEST_ASSERT_EQUAL(65535, color24to16(255, 255, 255));
    TEST_ASSERT_EQUAL(0xffff, color24to16(255, 255, 255));

    TEST_ASSERT_EQUAL( 63488, color24to16(255, 0, 0));
    TEST_ASSERT_EQUAL(0xf800, color24to16(255, 0, 0));
    TEST_ASSERT_EQUAL(  2016, color24to16(0, 255, 0));
    TEST_ASSERT_EQUAL(0x07e0, color24to16(0, 255, 0));
    TEST_ASSERT_EQUAL(    31, color24to16(0, 0, 255));
    TEST_ASSERT_EQUAL(0x001f, color24to16(0, 0, 255));

    TEST_ASSERT_EQUAL(65504, color24to16(255, 255, 0));
    TEST_ASSERT_EQUAL(63519, color24to16(255, 0, 255));
    TEST_ASSERT_EQUAL(2047, color24to16(0, 255, 255));
}
