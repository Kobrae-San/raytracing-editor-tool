#pragma once

#include <optional>

#include "geometry/hit_info.h"
#include "math/ray.h"

// Anything a ray can hit. The renderer only knows "a shape": a new shape is a
// new class and nothing else (open/closed).
//
// Contract every implementation must keep (Liskov): return the nearest hit in
// front of the ray's origin (t > 0) with a unit normal, or std::nullopt.
class Shape {
public:
    virtual ~Shape() = default;

    virtual std::optional<HitInfo> intersect(const Ray& ray) const = 0;
};
