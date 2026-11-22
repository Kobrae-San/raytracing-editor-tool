#include <catch2/catch_test_macros.hpp>

#include <memory>

#include "geometry/sphere.h"
#include "material/flat_shader.h"
#include "render/camera.h"
#include "test_helpers.h"

namespace {

// Eye one unit behind a 5-unit-wide screen: on a 5 x 3 image, one pixel is
// one unit wide.
const Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 5);

}  // namespace

TEST_CASE("rayThroughPixel goes from the eye through the pixel's centre", "[camera]") {
    SECTION("centre pixel (2, 1) points straight ahead") {
        Ray ray = camera.rayThroughPixel(2, 1, 5, 3);
        requireVectorsEqual(ray.origin(), Vector(0, 0, -1));
        requireVectorsEqual(ray.direction(), Vector(0, 0, 1));
    }
    SECTION("top-right pixel (4, 0): y is flipped") {
        requireVectorsEqual(camera.rayThroughPixel(4, 0, 5, 3).direction(), Vector(2, 1, 1));
    }
    SECTION("bottom-left pixel (0, 2)") {
        requireVectorsEqual(camera.rayThroughPixel(0, 2, 5, 3).direction(), Vector(-2, -1, 1));
    }
}

TEST_CASE("rayThroughPixel with another screen and image size", "[camera]") {
    Camera wide(Vector(0, 0, 0), Vector(0, 0, 1), 2.0);

    // pixel size 2 / 512; pixel (256, 128) is half a pixel right of and below the centre.
    requireVectorsEqual(wide.rayThroughPixel(256, 128, 512, 256).direction(),
                        Vector(0.001953125, -0.001953125, 1));
}

TEST_CASE("render: one traced ray per pixel", "[camera]") {
    Camera close(Vector(0, 0, -1), Vector(0, 0, 0), 5);
    Scene scene(Vector(0, 0, -1));
    scene.add(std::make_unique<Sphere>(Vector(0, 0, 6), 5, std::make_shared<FlatShader>(Colour(1, 0, 0))));

    Image image = close.render(scene, 5, 3);

    REQUIRE(image.width() == 5);
    REQUIRE(image.height() == 3);
    // The sphere covers a plus: the centre pixel and its four neighbours.
    for (unsigned int row = 0; row < 3; ++row) {
        for (unsigned int column = 0; column < 5; ++column) {
            bool inPlus = (column == 2) || (row == 1 && column >= 1 && column <= 3);
            requireColoursEqual(image.pixel(column, row), inPlus ? Colour(1, 0, 0) : Colour(0, 0, 0));
        }
    }
}
