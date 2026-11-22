#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "geometry/shape.h"
#include "math/vector.h"

// The shapes of the world, lit by one sun far away.
class Scene {
public:
    // toLight: direction from any point towards the sun. Stored normalised,
    // because Material::shade needs a unit vector.
    explicit Scene(const Vector& toLight);

    const Vector& toLight() const;

    void add(std::unique_ptr<Shape> shape);

    // The nearest hit among all shapes, or std::nullopt if the ray hits none.
    std::optional<HitInfo> nearestHit(const Ray& ray) const;

private:
    Vector _toLight;
    std::vector<std::unique_ptr<Shape>> _shapes;
};
