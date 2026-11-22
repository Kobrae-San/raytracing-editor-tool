#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <memory>

#include "geometry/sphere.h"
#include "material/flat_shader.h"

TEST_CASE("Sphere intersect finds the closest hit in front of the ray", "[sphere]") {
    auto material = std::make_shared<FlatShader>(Colour(0, 1, 0));
    Sphere sphere(Vector(0, 0, 5), 1, material);

    Ray ray(Vector(0, 0, 0), Vector(0, 0, 1));

    auto hit = sphere.intersect(ray);

    REQUIRE(hit.has_value());

    // Closest intersection: t = 4, so the hit point is (0, 0, 4).
    REQUIRE(hit->point.x() == Catch::Approx(0.0));
    REQUIRE(hit->point.y() == Catch::Approx(0.0));
    REQUIRE(hit->point.z() == Catch::Approx(4.0));

    // Normal points from the center (0,0,5) towards the hit point (0,0,4).
    REQUIRE(hit->normal.x() == Catch::Approx(0.0));
    REQUIRE(hit->normal.y() == Catch::Approx(0.0));
    REQUIRE(hit->normal.z() == Catch::Approx(-1.0));

    REQUIRE(hit->material == material);
}

TEST_CASE("Sphere intersect returns no hit when the ray misses", "[sphere]") {
    auto material = std::make_shared<FlatShader>(Colour(0, 1, 0));
    Sphere sphere(Vector(0, 0, 5), 1, material);

    Ray ray(Vector(0, 0, 0), Vector(1, 0, 0));

    auto hit = sphere.intersect(ray);

    REQUIRE_FALSE(hit.has_value());
}
