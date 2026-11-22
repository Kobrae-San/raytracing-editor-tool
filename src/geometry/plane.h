#pragma once

#include <memory>
#include <optional>

#include "geometry/shape.h"
#include "math/vector.h"

// An infinite plane through a point, facing along a normal (e.g. a floor).
class Plane : public Shape {
public:
    // normal need not be unit length: the plane stores it normalised.
    Plane(const Vector& point, const Vector& normal, std::shared_ptr<const Material> material);

    std::optional<HitInfo> intersect(const Ray& ray) const override;

private:
    Vector _point;
    Vector _normal;
    std::shared_ptr<const Material> _material;
};
