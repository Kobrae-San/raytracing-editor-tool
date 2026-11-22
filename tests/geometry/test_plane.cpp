#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <memory>

#include "geometry/plane.h"
#include "material/flat_shader.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

namespace {

const auto green = std::make_shared<FlatShader>(Colour(0, 1, 0));

}  // namespace

TEST_CASE("Floor hit from above", "[plane]") {
    Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), green);

    auto hit = floor.intersect(Ray(Vector(0, 8, 0), Vector(3, -4, 0)));

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(2.0, tolerance));
    requireVectorsEqual(hit->point, Vector(6, 0, 0));
    requireVectorsEqual(hit->normal, Vector(0, 1, 0));
    REQUIRE(hit->material == green.get());
}

TEST_CASE("Tilted plane 3x + 4y = 24: the normal is stored unit length", "[plane]") {
    Plane plane(Vector(8, 0, 0), Vector(3, 4, 0), green);

    auto hit = plane.intersect(Ray(Vector(-8, 0, 0), Vector(4, 3, 0)));

    REQUIRE(hit.has_value());
    REQUIRE_THAT(hit->t, WithinAbs(2.0, tolerance));
    requireVectorsEqual(hit->point, Vector(0, 6, 0));
    requireVectorsEqual(hit->normal, Vector(0.6, 0.8, 0));
}

TEST_CASE("Ray parallel to the floor: no hit", "[plane]") {
    Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), green);

    REQUIRE_FALSE(floor.intersect(Ray(Vector(0, 8, 0), Vector(5, 0, 0))).has_value());
}

TEST_CASE("Floor behind the ray: no hit", "[plane]") {
    Plane floor(Vector(0, 0, 0), Vector(0, 1, 0), green);

    REQUIRE_FALSE(floor.intersect(Ray(Vector(0, 8, 0), Vector(3, 4, 0))).has_value());
}
