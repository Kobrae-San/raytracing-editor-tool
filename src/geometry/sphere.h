#pragma once

#include <memory>
#include <optional>

#include "geometry/hit_info.h"
#include "material/material.h"
#include "math/ray.h"
#include "math/vector.h"

// A sphere shape: a center point and a radius. One of the shapes a ray can
// be tested against in the scene.
class Sphere {
public:
    Sphere(const Vector& center, double radius, std::shared_ptr<Material> material);

    // Read-only access to the components.
    const Vector& center() const;  // returned by reference: Vector is an object
    double radius() const;         // returned by value: just a number
    const std::shared_ptr<Material>& material() const;

    // The closest point (at a non-negative distance along ray) where ray
    // hits this sphere, or std::nullopt if it misses entirely.
    std::optional<HitInfo> intersect(const Ray& ray) const;

private:
    Vector _center;
    double _radius;
    std::shared_ptr<Material> _material;
};
