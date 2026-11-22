#include <catch2/catch_test_macros.hpp>

#include "material/flat_shader.h"
#include "material/lambert_shader.h"
#include "test_helpers.h"

namespace {

HitInfo hitFacing(const Vector& normal) {
    return HitInfo{1.0, Vector(0, 0, 0), normal, nullptr};
}

const Colour orange(1, 0.5, 0);
const HitInfo facingTheEye = hitFacing(Vector(0, 0, -1));

}  // namespace

TEST_CASE("Lambert: brightness is N . L", "[material]") {
    LambertShader material(orange);

    SECTION("light straight on: full colour") {
        requireColoursEqual(material.shade(facingTheEye, Vector(0, 0, -1)), Colour(1, 0.5, 0));
    }
    SECTION("light at an angle: N . L = 0.8") {
        requireColoursEqual(material.shade(facingTheEye, Vector(0.6, 0, -0.8)), Colour(0.8, 0.4, 0));
    }
    SECTION("light at a right angle: black") {
        requireColoursEqual(material.shade(facingTheEye, Vector(1, 0, 0)), Colour(0, 0, 0));
    }
    SECTION("light behind the surface: black, never negative") {
        requireColoursEqual(material.shade(facingTheEye, Vector(0, 0, 1)), Colour(0, 0, 0));
    }
}

TEST_CASE("Flat: the same colour whatever the light", "[material]") {
    FlatShader material(orange);

    requireColoursEqual(material.shade(facingTheEye, Vector(0, 0, -1)), orange);
    requireColoursEqual(material.shade(facingTheEye, Vector(0, 0, 1)), orange);
}
