#include "unity.h"
#include <PixelLocator.h>

TEST_CASE("PixelLocator: DEFAULTS (horizontal, serpentine)", "[Matrix]")
{
    auto pl = PixelLocator(3, 3, DefaultOptions);

    TEST_ASSERT_EQUAL(0, pl.xyToIndex(0, 0));
    TEST_ASSERT_EQUAL(1, pl.xyToIndex(1, 0));
    TEST_ASSERT_EQUAL(2, pl.xyToIndex(2, 0));

    TEST_ASSERT_EQUAL(5, pl.xyToIndex(0, 1));
    TEST_ASSERT_EQUAL(4, pl.xyToIndex(1, 1));
    TEST_ASSERT_EQUAL(3, pl.xyToIndex(2, 1));

    TEST_ASSERT_EQUAL(6, pl.xyToIndex(0, 2));
    TEST_ASSERT_EQUAL(7, pl.xyToIndex(1, 2));
    TEST_ASSERT_EQUAL(8, pl.xyToIndex(2, 2));
}

TEST_CASE("PixelLocator: horizontal, serpentine", "[Matrix]")
{
    auto pl = PixelLocator(3, 3, MatrixHorizontal|MatrixSerpentine);

    TEST_ASSERT_EQUAL(0, pl.xyToIndex(0, 0));
    TEST_ASSERT_EQUAL(1, pl.xyToIndex(1, 0));
    TEST_ASSERT_EQUAL(2, pl.xyToIndex(2, 0));

    TEST_ASSERT_EQUAL(5, pl.xyToIndex(0, 1));
    TEST_ASSERT_EQUAL(4, pl.xyToIndex(1, 1));
    TEST_ASSERT_EQUAL(3, pl.xyToIndex(2, 1));

    TEST_ASSERT_EQUAL(6, pl.xyToIndex(0, 2));
    TEST_ASSERT_EQUAL(7, pl.xyToIndex(1, 2));
    TEST_ASSERT_EQUAL(8, pl.xyToIndex(2, 2));
}

TEST_CASE("PixelLocator: horizontal, straight", "[Matrix]")
{
    auto pl = PixelLocator(3, 3, MatrixHorizontal|MatrixStraight);

    TEST_ASSERT_EQUAL(0, pl.xyToIndex(0, 0));
    TEST_ASSERT_EQUAL(1, pl.xyToIndex(1, 0));
    TEST_ASSERT_EQUAL(2, pl.xyToIndex(2, 0));

    TEST_ASSERT_EQUAL(3, pl.xyToIndex(0, 1));
    TEST_ASSERT_EQUAL(4, pl.xyToIndex(1, 1));
    TEST_ASSERT_EQUAL(5, pl.xyToIndex(2, 1));

    TEST_ASSERT_EQUAL(6, pl.xyToIndex(0, 2));
    TEST_ASSERT_EQUAL(7, pl.xyToIndex(1, 2));
    TEST_ASSERT_EQUAL(8, pl.xyToIndex(2, 2));
}

TEST_CASE("PixelLocator: vertical, serpentine", "[Matrix]")
{
    auto pl = PixelLocator(3, 3, MatrixVertical|MatrixSerpentine);

    TEST_ASSERT_EQUAL(0, pl.xyToIndex(0, 0));
    TEST_ASSERT_EQUAL(5, pl.xyToIndex(1, 0));
    TEST_ASSERT_EQUAL(6, pl.xyToIndex(2, 0));

    TEST_ASSERT_EQUAL(1, pl.xyToIndex(0, 1));
    TEST_ASSERT_EQUAL(4, pl.xyToIndex(1, 1));
    TEST_ASSERT_EQUAL(7, pl.xyToIndex(2, 1));

    TEST_ASSERT_EQUAL(2, pl.xyToIndex(0, 2));
    TEST_ASSERT_EQUAL(3, pl.xyToIndex(1, 2));
    TEST_ASSERT_EQUAL(8, pl.xyToIndex(2, 2));
}

TEST_CASE("PixelLocator: vertical, straight", "[Matrix]")
{
    auto pl = PixelLocator(3, 3, MatrixVertical|MatrixStraight);

    TEST_ASSERT_EQUAL(0, pl.xyToIndex(0, 0));
    TEST_ASSERT_EQUAL(3, pl.xyToIndex(1, 0));
    TEST_ASSERT_EQUAL(6, pl.xyToIndex(2, 0));

    TEST_ASSERT_EQUAL(1, pl.xyToIndex(0, 1));
    TEST_ASSERT_EQUAL(4, pl.xyToIndex(1, 1));
    TEST_ASSERT_EQUAL(7, pl.xyToIndex(2, 1));

    TEST_ASSERT_EQUAL(2, pl.xyToIndex(0, 2));
    TEST_ASSERT_EQUAL(5, pl.xyToIndex(1, 2));
    TEST_ASSERT_EQUAL(8, pl.xyToIndex(2, 2));
}

TEST_CASE("PixelLocator: horizontal, serpentine, invert horizontal", "[Matrix]")
{
    auto pl = PixelLocator(3, 3, MatrixHorizontal|MatrixSerpentine|MatrixInvertHorizontal);

    TEST_ASSERT_EQUAL(2, pl.xyToIndex(0, 0));
    TEST_ASSERT_EQUAL(1, pl.xyToIndex(1, 0));
    TEST_ASSERT_EQUAL(0, pl.xyToIndex(2, 0));

    TEST_ASSERT_EQUAL(3, pl.xyToIndex(0, 1));
    TEST_ASSERT_EQUAL(4, pl.xyToIndex(1, 1));
    TEST_ASSERT_EQUAL(5, pl.xyToIndex(2, 1));

    TEST_ASSERT_EQUAL(8, pl.xyToIndex(0, 2));
    TEST_ASSERT_EQUAL(7, pl.xyToIndex(1, 2));
    TEST_ASSERT_EQUAL(6, pl.xyToIndex(2, 2));
}

TEST_CASE("PixelLocator: horizontal, straight, invert horizontal", "[Matrix]")
{
    auto pl = PixelLocator(3, 3, MatrixHorizontal|MatrixStraight|MatrixInvertHorizontal);

    TEST_ASSERT_EQUAL(2, pl.xyToIndex(0, 0));
    TEST_ASSERT_EQUAL(1, pl.xyToIndex(1, 0));
    TEST_ASSERT_EQUAL(0, pl.xyToIndex(2, 0));

    TEST_ASSERT_EQUAL(5, pl.xyToIndex(0, 1));
    TEST_ASSERT_EQUAL(4, pl.xyToIndex(1, 1));
    TEST_ASSERT_EQUAL(3, pl.xyToIndex(2, 1));

    TEST_ASSERT_EQUAL(8, pl.xyToIndex(0, 2));
    TEST_ASSERT_EQUAL(7, pl.xyToIndex(1, 2));
    TEST_ASSERT_EQUAL(6, pl.xyToIndex(2, 2));
}

TEST_CASE("PixelLocator: vertical, serpentine, invert horizontal", "[Matrix]")
{
    auto pl = PixelLocator(3, 3, MatrixVertical|MatrixSerpentine|MatrixInvertHorizontal);

    TEST_ASSERT_EQUAL(6, pl.xyToIndex(0, 0));
    TEST_ASSERT_EQUAL(5, pl.xyToIndex(1, 0));
    TEST_ASSERT_EQUAL(0, pl.xyToIndex(2, 0));

    TEST_ASSERT_EQUAL(7, pl.xyToIndex(0, 1));
    TEST_ASSERT_EQUAL(4, pl.xyToIndex(1, 1));
    TEST_ASSERT_EQUAL(1, pl.xyToIndex(2, 1));

    TEST_ASSERT_EQUAL(8, pl.xyToIndex(0, 2));
    TEST_ASSERT_EQUAL(3, pl.xyToIndex(1, 2));
    TEST_ASSERT_EQUAL(2, pl.xyToIndex(2, 2));
}

TEST_CASE("PixelLocator: vertical, straight, invert horizontal", "[Matrix]")
{
    auto pl = PixelLocator(3, 3, MatrixVertical|MatrixStraight|MatrixInvertHorizontal);

    TEST_ASSERT_EQUAL(6, pl.xyToIndex(0, 0));
    TEST_ASSERT_EQUAL(3, pl.xyToIndex(1, 0));
    TEST_ASSERT_EQUAL(0, pl.xyToIndex(2, 0));

    TEST_ASSERT_EQUAL(7, pl.xyToIndex(0, 1));
    TEST_ASSERT_EQUAL(4, pl.xyToIndex(1, 1));
    TEST_ASSERT_EQUAL(1, pl.xyToIndex(2, 1));

    TEST_ASSERT_EQUAL(8, pl.xyToIndex(0, 2));
    TEST_ASSERT_EQUAL(5, pl.xyToIndex(1, 2));
    TEST_ASSERT_EQUAL(2, pl.xyToIndex(2, 2));
}

TEST_CASE("PixelLocator: horizontal, serpentine, invert vertical", "[Matrix]")
{
    auto pl = PixelLocator(3, 3, MatrixHorizontal|MatrixSerpentine|MatrixInvertVertical);

    TEST_ASSERT_EQUAL(6, pl.xyToIndex(0, 0));
    TEST_ASSERT_EQUAL(7, pl.xyToIndex(1, 0));
    TEST_ASSERT_EQUAL(8, pl.xyToIndex(2, 0));

    TEST_ASSERT_EQUAL(5, pl.xyToIndex(0, 1));
    TEST_ASSERT_EQUAL(4, pl.xyToIndex(1, 1));
    TEST_ASSERT_EQUAL(3, pl.xyToIndex(2, 1));

    TEST_ASSERT_EQUAL(0, pl.xyToIndex(0, 2));
    TEST_ASSERT_EQUAL(1, pl.xyToIndex(1, 2));
    TEST_ASSERT_EQUAL(2, pl.xyToIndex(2, 2));
}

TEST_CASE("PixelLocator: horizontal, straight, invert vertical", "[Matrix]")
{
    auto pl = PixelLocator(3, 3, MatrixHorizontal|MatrixStraight|MatrixInvertVertical);

    TEST_ASSERT_EQUAL(6, pl.xyToIndex(0, 0));
    TEST_ASSERT_EQUAL(7, pl.xyToIndex(1, 0));
    TEST_ASSERT_EQUAL(8, pl.xyToIndex(2, 0));

    TEST_ASSERT_EQUAL(3, pl.xyToIndex(0, 1));
    TEST_ASSERT_EQUAL(4, pl.xyToIndex(1, 1));
    TEST_ASSERT_EQUAL(5, pl.xyToIndex(2, 1));

    TEST_ASSERT_EQUAL(0, pl.xyToIndex(0, 2));
    TEST_ASSERT_EQUAL(1, pl.xyToIndex(1, 2));
    TEST_ASSERT_EQUAL(2, pl.xyToIndex(2, 2));
}

TEST_CASE("PixelLocator: vertical, serpentine, invert vertical", "[Matrix]")
{
    auto pl = PixelLocator(3, 3, MatrixVertical|MatrixSerpentine|MatrixInvertVertical);

    TEST_ASSERT_EQUAL(2, pl.xyToIndex(0, 0));
    TEST_ASSERT_EQUAL(3, pl.xyToIndex(1, 0));
    TEST_ASSERT_EQUAL(8, pl.xyToIndex(2, 0));

    TEST_ASSERT_EQUAL(1, pl.xyToIndex(0, 1));
    TEST_ASSERT_EQUAL(4, pl.xyToIndex(1, 1));
    TEST_ASSERT_EQUAL(7, pl.xyToIndex(2, 1));

    TEST_ASSERT_EQUAL(0, pl.xyToIndex(0, 2));
    TEST_ASSERT_EQUAL(5, pl.xyToIndex(1, 2));
    TEST_ASSERT_EQUAL(6, pl.xyToIndex(2, 2));
}

TEST_CASE("PixelLocator: vertical, straight, invert vertical", "[Matrix]")
{
    auto pl = PixelLocator(3, 3, MatrixVertical|MatrixStraight|MatrixInvertVertical);

    TEST_ASSERT_EQUAL(2, pl.xyToIndex(0, 0));
    TEST_ASSERT_EQUAL(5, pl.xyToIndex(1, 0));
    TEST_ASSERT_EQUAL(8, pl.xyToIndex(2, 0));

    TEST_ASSERT_EQUAL(1, pl.xyToIndex(0, 1));
    TEST_ASSERT_EQUAL(4, pl.xyToIndex(1, 1));
    TEST_ASSERT_EQUAL(7, pl.xyToIndex(2, 1));

    TEST_ASSERT_EQUAL(0, pl.xyToIndex(0, 2));
    TEST_ASSERT_EQUAL(3, pl.xyToIndex(1, 2));
    TEST_ASSERT_EQUAL(6, pl.xyToIndex(2, 2));
}
