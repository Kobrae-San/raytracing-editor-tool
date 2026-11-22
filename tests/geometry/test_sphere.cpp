#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <memory>

#include "geometry/sphere.h"
#include "material/flat_shader.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

namespace {

// Eye at (0, 0, -1), looking along z.
const Ray rayAlongZ(Vector(0, 0, -1), Vector(0, 0, 1));

const auto red = std::make_shared<FlatShader>(Colour(1, 0, 0));

}  // namespace

TEST_CASE("Sphere straight ahead: nearest hit, normal and material", "[sphere]") {
    Sphere sphere(Vector(0, 0, 9), 5, red);

    auto hit = sphere.intersect(rayAlongZ);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(5.0, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 4));
    requireVectorsEqual(hit->normal, Vector(0, 0, -1));
    REQUIRE(hit->material == red.get());
}

TEST_CASE("Sphere off-centre: hit with a tilted normal", "[sphere]") {
    // c = 84 here; a radius not squared would give a miss (discriminant -16).
    Sphere sphere(Vector(3, 0, 9), 5, red);

    auto hit = sphere.intersect(rayAlongZ);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(6.0, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 5));
    requireVectorsEqual(hit->normal, Vector(-0.6, 0, -0.8));
}

TEST_CASE("Sphere beside the ray: no hit", "[sphere]") {
    Sphere sphere(Vector(6, 0, 9), 5, red);

    REQUIRE_FALSE(sphere.intersect(rayAlongZ).has_value());
}

TEST_CASE("Sphere behind the eye: no hit", "[sphere]") {
    // t = -5 or -15: both behind the origin.
    Sphere sphere(Vector(0, 0, -11), 5, red);

    REQUIRE_FALSE(sphere.intersect(rayAlongZ).has_value());
}

TEST_CASE("Ray starting inside the sphere hits its far side", "[sphere]") {
    Sphere sphere(Vector(0, 0, 1), 5, red);

    auto hit = sphere.intersect(rayAlongZ);

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(7.0, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 0, 6));
    requireVectorsEqual(hit->normal, Vector(0, 0, 1));
}
