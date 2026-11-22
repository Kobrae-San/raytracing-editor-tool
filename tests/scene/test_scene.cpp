#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <memory>

#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "material/flat_shader.h"
#include "scene/scene.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

namespace {

const Ray rayAlongZ(Vector(0, 0, -1), Vector(0, 0, 1));
const auto red = std::make_shared<FlatShader>(Colour(1, 0, 0));
const auto blue = std::make_shared<FlatShader>(Colour(0, 0, 1));

std::unique_ptr<Shape> sphereAt(const Vector& center) {
    return std::make_unique<Sphere>(center, 5, red);
}

std::unique_ptr<Shape> wallThrough(const Vector& point) {
    return std::make_unique<Plane>(point, Vector(0, 0, -1), blue);
}

}  // namespace

TEST_CASE("Scene stores the sun direction normalised", "[scene]") {
    Scene scene(Vector(0, 3, -4));

    requireVectorsEqual(scene.toLight(), Vector(0, 0.6, -0.8));
}

TEST_CASE("Scene returns the nearest hit, whatever the order of the shapes", "[scene]") {
    Scene scene(Vector(0, 0, -1));

    SECTION("the nearer shape is added second") {
        scene.add(sphereAt(Vector(0, 0, 9)));
        scene.add(wallThrough(Vector(0, 0, 2)));

        auto hit = scene.nearestHit(rayAlongZ);

        REQUIRE(hit.has_value());
        REQUIRE_THAT(hit->t, WithinAbs(3.0, tolerance));
        REQUIRE(hit->material == blue.get());
    }
    SECTION("the nearer shape is added first") {
        scene.add(sphereAt(Vector(0, 0, 9)));
        scene.add(wallThrough(Vector(0, 0, 20)));

        auto hit = scene.nearestHit(rayAlongZ);

        REQUIRE(hit.has_value());
        REQUIRE_THAT(hit->t, WithinAbs(5.0, tolerance));
        REQUIRE(hit->material == red.get());
    }
}

TEST_CASE("Scene: no hit when every shape is missed", "[scene]") {
    Scene scene(Vector(0, 0, -1));
    scene.add(sphereAt(Vector(6, 0, 9)));

    REQUIRE_FALSE(scene.nearestHit(rayAlongZ).has_value());
}
