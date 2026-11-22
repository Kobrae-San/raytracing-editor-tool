#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "math/ray.h"

TEST_CASE("Ray at() finds the point travelled along the ray", "[ray]") {
    Ray ray(Vector(0, 0, 0), Vector(1, 2, 3));

    Vector point = ray.at(2.0);

    // origin + direction * t = (0,0,0) + (1,2,3) * 2 = (2,4,6)
    REQUIRE(point.x() == Catch::Approx(2.0));
    REQUIRE(point.y() == Catch::Approx(4.0));
    REQUIRE(point.z() == Catch::Approx(6.0));
}
