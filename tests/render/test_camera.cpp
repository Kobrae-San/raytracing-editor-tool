#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "render/camera.h"

namespace {

void requireDirection(const Vector& direction, double x, double y, double z) {
    REQUIRE(direction.x() == Catch::Approx(x));
    REQUIRE(direction.y() == Catch::Approx(y));
    REQUIRE(direction.z() == Catch::Approx(z));
}

}  // namespace

TEST_CASE("Camera rayThroughPixel points through the right pixel", "[camera]") {
    Camera camera(Vector(0, 0, 0));

    const unsigned int imageWidth = 5;
    const unsigned int imageHeight = 3;
    const double screenWidth = 5;

    SECTION("centre pixel (2, 1) points straight ahead") {
        Ray ray = camera.rayThroughPixel(2, 1, imageWidth, imageHeight, screenWidth);
        requireDirection(ray.direction(), 0, 0, 1);
    }

    SECTION("top-right pixel (4, 0)") {
        Ray ray = camera.rayThroughPixel(4, 0, imageWidth, imageHeight, screenWidth);
        requireDirection(ray.direction(), 2, 1, 1);
    }

    SECTION("bottom-left pixel (0, 2)") {
        Ray ray = camera.rayThroughPixel(0, 2, imageWidth, imageHeight, screenWidth);
        requireDirection(ray.direction(), -2, -1, 1);
    }
}

TEST_CASE("Camera rayThroughPixel works with a different screen/image size", "[camera]") {
    Camera camera(Vector(0, 0, 0));

    Ray ray = camera.rayThroughPixel(256, 128, 512, 256, 2.0);
    requireDirection(ray.direction(), 0.001953125, -0.001953125, 1);
}
