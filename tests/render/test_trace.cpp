#include <catch2/catch_test_macros.hpp>

#include <memory>

#include "geometry/sphere.h"
#include "material/lambert_shader.h"
#include "render/trace.h"
#include "test_helpers.h"

namespace {

const Ray rayAlongZ(Vector(0, 0, -1), Vector(0, 0, 1));

Scene redBallAt(const Vector& center, const Vector& toLight) {
    Scene scene(toLight);
    scene.add(std::make_unique<Sphere>(center, 5, std::make_shared<LambertShader>(Colour(1, 0, 0))));
    return scene;
}

}  // namespace

TEST_CASE("trace shades the nearest surface with the sun", "[trace]") {
    SECTION("sun behind the eye: full red") {
        requireColoursEqual(trace(rayAlongZ, redBallAt(Vector(0, 0, 9), Vector(0, 0, -1))), Colour(1, 0, 0));
    }
    SECTION("sun at an angle: N . L = 0.8") {
        requireColoursEqual(trace(rayAlongZ, redBallAt(Vector(0, 0, 9), Vector(0.6, 0, -0.8))), Colour(0.8, 0, 0));
    }
    SECTION("off-centre ball, tilted normal: N . L = 0.8") {
        requireColoursEqual(trace(rayAlongZ, redBallAt(Vector(3, 0, 9), Vector(0, 0, -1))), Colour(0.8, 0, 0));
    }
}

TEST_CASE("trace returns black when the ray hits nothing", "[trace]") {
    requireColoursEqual(trace(rayAlongZ, redBallAt(Vector(6, 0, 9), Vector(0, 0, -1))), Colour(0, 0, 0));
}
