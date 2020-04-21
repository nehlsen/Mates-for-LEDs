#include "unity.h"
#include <PixelMap.h>

TEST_CASE("PixelMap: add, has", "[Matrix]")
{
    auto pm = PixelMap();
    auto pixel1 = Pixel(1, 2, CRGB(11, 22, 33));
    auto pixel1b = Pixel(1, 2, CRGB(99, 99, 99));
    auto pixel2 = Pixel(5, 6, CRGB(111, 122, 133));

    TEST_ASSERT_EQUAL(0, pm.size());
    TEST_ASSERT_FALSE(pm.has(pixel1));
    TEST_ASSERT_FALSE(pm.has(pixel1b));
    TEST_ASSERT_FALSE(pm.has(pixel2));

    pm.add(pixel1);
    TEST_ASSERT_EQUAL(1, pm.size());
    TEST_ASSERT_TRUE(pm.has(pixel1));
    TEST_ASSERT_EQUAL(pixel1.getColor().r, pm.at(pixel1).getColor().r);
    TEST_ASSERT_FALSE(pm.has(pixel2));

    pm.add(pixel1b);
    TEST_ASSERT_EQUAL(1, pm.size());
    TEST_ASSERT_TRUE(pm.has(pixel1b));
    TEST_ASSERT_EQUAL(pixel1b.getColor().r, pm.at(pixel1b).getColor().r);
    TEST_ASSERT_FALSE(pm.has(pixel2));

    pm.add(pixel2);
    TEST_ASSERT_EQUAL(2, pm.size());
    TEST_ASSERT_TRUE(pm.has(pixel1b));
    TEST_ASSERT_EQUAL(pixel1b.getColor().r, pm.at(pixel1b).getColor().r);
    TEST_ASSERT_TRUE(pm.has(pixel2));

    pm.clear();
    TEST_ASSERT_EQUAL(0, pm.size());
    TEST_ASSERT_FALSE(pm.has(pixel1));
    TEST_ASSERT_FALSE(pm.has(pixel1b));
    TEST_ASSERT_FALSE(pm.has(pixel2));

    Pixels pixels = {pixel1, pixel1b, pixel2};
    pm.add(pixels);
    TEST_ASSERT_EQUAL(3, pixels.size());
    TEST_ASSERT_EQUAL(2, pm.size());
    TEST_ASSERT_TRUE(pm.has(pixel1b));
    TEST_ASSERT_EQUAL(pixel1b.getColor().r, pm.at(pixel1b).getColor().r);
    TEST_ASSERT_TRUE(pm.has(pixel2));
}

TEST_CASE("PixelMap: factory, toPixels", "[Matrix]")
{
    auto pm = PixelMap();
    auto pixel1 = Pixel(1, 2, CRGB(11, 22, 33));
    auto pixel1b = Pixel(1, 2, CRGB(99, 99, 99));
    auto pixel2 = Pixel(5, 6, CRGB(111, 122, 133));
    Pixels pixels = {pixel1, pixel1b, pixel2};

    TEST_ASSERT_EQUAL(0, pm.size());
    TEST_ASSERT_FALSE(pm.has(pixel1));
    TEST_ASSERT_FALSE(pm.has(pixel1b));
    TEST_ASSERT_FALSE(pm.has(pixel2));

    pm = PixelMap::fromPixels(pixels);
    TEST_ASSERT_EQUAL(2, pm.size());
    TEST_ASSERT_TRUE(pm.has(pixel1b));
    TEST_ASSERT_EQUAL(pixel1b.getColor().r, pm.at(pixel1b).getColor().r);
    TEST_ASSERT_TRUE(pm.has(pixel2));

    Pixels pixels2 = pm.toPixels();
    TEST_ASSERT_EQUAL(2, pixels2.size());

    TEST_ASSERT_EQUAL(1, pixels2[0].getX());
    TEST_ASSERT_EQUAL(2, pixels2[0].getY());
    TEST_ASSERT_EQUAL(99, pixels2[0].getColor().r);

    TEST_ASSERT_EQUAL(5, pixels2[1].getX());
    TEST_ASSERT_EQUAL(6, pixels2[1].getY());
    TEST_ASSERT_EQUAL(111, pixels2[1].getColor().r);
}