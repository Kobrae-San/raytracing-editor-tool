#pragma once

#include "math/vector.h"

// A ray is a half-line: it starts at a point (origin) and travels in a
// direction. It is the core thing a raytracer shoots through a scene.
class Ray {
public:
    Ray(const Vector& origin, const Vector& direction);

    // Read-only access to the two components.
    // Returned by const reference to avoid copying the Vector.
    const Vector& origin() const;
    const Vector& direction() const;

    // The point reached by travelling a distance t along this ray, starting
    // from its origin: origin + direction * t.
    Vector at(double t) const;

private:
    Vector _origin;
    Vector _direction;
};
