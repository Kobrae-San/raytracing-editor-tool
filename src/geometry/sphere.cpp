#include "geometry/sphere.h"

#include <cmath>

Sphere::Sphere(const Vector& center, double radius, std::shared_ptr<Material> material)
    : _center(center), _radius(radius), _material(std::move(material)) {
}

const Vector& Sphere::center() const {
    return _center;
}

double Sphere::radius() const {
    return _radius;
}

const std::shared_ptr<Material>& Sphere::material() const {
    return _material;
}

std::optional<HitInfo> Sphere::intersect(const Ray& ray) const {
    // Classic ray-sphere intersection: solve |O + tD - C|^2 = r^2 for t and
    // check whether the resulting quadratic has a real, non-negative solution.
    Vector originToCenter = ray.origin() - _center;
    double a = ray.direction().dot(ray.direction());
    double b = 2.0 * originToCenter.dot(ray.direction());
    double c = originToCenter.dot(originToCenter) - _radius * _radius;
    double discriminant = b * b - 4.0 * a * c;

    if (discriminant < 0.0) {
        return std::nullopt;
    }

    double sqrtDiscriminant = std::sqrt(discriminant);
    double closerT = (-b - sqrtDiscriminant) / (2.0 * a);
    double fartherT = (-b + sqrtDiscriminant) / (2.0 * a);

    double t;
    if (closerT >= 0.0) {
        t = closerT;
    } else if (fartherT >= 0.0) {
        t = fartherT;
    } else {
        // Both intersections are behind the ray's origin.
        return std::nullopt;
    }

    HitInfo hit;
    hit.point = ray.at(t);
    hit.normal = (hit.point - _center).normalised();
    hit.material = _material;
    return hit;
}
