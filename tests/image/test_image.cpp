#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "image/image.h"

TEST_CASE("Image setPixel sets only the targeted pixel", "[image]") {
    Image image(5, 4);

    Colour green(0.0, 1.0, 0.0);
    image.setPixel(3, 2, green);

    for (unsigned int y = 0; y < image.height(); ++y) {
        for (unsigned int x = 0; x < image.width(); ++x) {
            const Colour& pixel = image.pixel(x, y);

            if (x == 3 && y == 2) {
                REQUIRE(pixel.r() == Catch::Approx(0.0));
                REQUIRE(pixel.g() == Catch::Approx(1.0));
                REQUIRE(pixel.b() == Catch::Approx(0.0));
            } else {
                REQUIRE(pixel.r() == Catch::Approx(0.0));
                REQUIRE(pixel.g() == Catch::Approx(0.0));
                REQUIRE(pixel.b() == Catch::Approx(0.0));
            }
        }
    }
}
