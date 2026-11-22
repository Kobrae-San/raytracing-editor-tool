#include <catch2/catch_test_macros.hpp>

#include "image/image.h"
#include "test_helpers.h"

TEST_CASE("Image knows its size", "[image]") {
    Image image(5, 3);

    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);
}

TEST_CASE("Image starts all black", "[image]") {
    Image image(5, 3);

    for (unsigned int y = 0; y < image.height(); ++y) {
        for (unsigned int x = 0; x < image.width(); ++x) {
            requireColoursEqual(image.pixel(x, y), Colour(0, 0, 0));
        }
    }
}

TEST_CASE("Image setPixel changes only the targeted pixel", "[image]") {
    // Odd-sized, non-square image and an off-centre pixel: a swapped x/y or
    // a wrong row length would show up here.
    Image image(5, 3);
    image.setPixel(4, 0, Colour(1, 0, 0));

    for (unsigned int y = 0; y < image.height(); ++y) {
        for (unsigned int x = 0; x < image.width(); ++x) {
            Colour expected = (x == 4 && y == 0) ? Colour(1, 0, 0) : Colour(0, 0, 0);
            requireColoursEqual(image.pixel(x, y), expected);
        }
    }
}
