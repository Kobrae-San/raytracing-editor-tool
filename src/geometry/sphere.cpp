#include "geometry/sphere.h"

#include <cmath>

Sphere::Sphere(const Vector& center, double radius, std::shared_ptr<const Material> material)
    : _center(center), _radius(radius), _material(std::move(material)) {
}

const Vector& Sphere::center() const {
    return _center;
}

double Sphere::radius() const {
    return _radius;
}

std::optional<HitInfo> Sphere::intersect(const Ray& ray) const {
    // Solve |O + tD - C|^2 = r^2: a t^2 + b t + c = 0 with L = O - C.
    Vector originToCenter = ray.origin() - _center;
    double a = ray.direction().dot(ray.direction());
    double b = 2.0 * originToCenter.dot(ray.direction());
    double c = originToCenter.dot(originToCenter) - _radius * _radius;
    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return std::nullopt;
    }

    double root = std::sqrt(discriminant);
    double nearT = (-b - root) / (2.0 * a);
    double farT = (-b + root) / (2.0 * a);

    double t;
    if (nearT > 0.0) {
        t = nearT;
    } else if (farT > 0.0) {
        // The ray starts inside the sphere.
        t = farT;
    } else {
        // Both intersections are behind the ray's origin.
        return std::nullopt;
    }

    Vector point = ray.at(t);
    Vector normal = (1.0 / _radius) * (point - _center);
    return HitInfo{t, point, normal, _material.get()};
}
