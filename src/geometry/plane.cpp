#include "geometry/plane.h"

Plane::Plane(const Vector& point, const Vector& normal, std::shared_ptr<const Material> material)
    : _point(point), _normal(normal.normalised()), _material(std::move(material)) {
}

std::optional<HitInfo> Plane::intersect(const Ray& ray) const {
    // Points P on the plane satisfy n . (P - Q) = 0. With P = O + tD:
    // t = n . (Q - O) / (n . D).
    double normalDotDirection = _normal.dot(ray.direction());
    if (normalDotDirection == 0.0) {
        // The ray is parallel to the plane.
        return std::nullopt;
    }

    double t = _normal.dot(_point - ray.origin()) / normalDotDirection;
    if (t <= 0.0) {
        // The plane is behind the ray's origin.
        return std::nullopt;
    }

    return HitInfo{t, ray.at(t), _normal, _material.get()};
}
