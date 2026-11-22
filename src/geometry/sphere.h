#pragma once

#include <memory>
#include <optional>

#include "geometry/shape.h"
#include "math/vector.h"

class Sphere : public Shape {
public:
    // A sphere has a material (ADR 0011): it delegates shading to it.
    Sphere(const Vector& center, double radius, std::shared_ptr<const Material> material);

    const Vector& center() const;
    double radius() const;

    std::optional<HitInfo> intersect(const Ray& ray) const override;

private:
    Vector _center;
    double _radius;
    std::shared_ptr<const Material> _material;
};
