#include "scene/scene.h"

Scene::Scene(const Vector& toLight)
    : _toLight(toLight.normalised()) {
}

const Vector& Scene::toLight() const {
    return _toLight;
}

void Scene::add(std::unique_ptr<Shape> shape) {
    _shapes.push_back(std::move(shape));
}

std::optional<HitInfo> Scene::nearestHit(const Ray& ray) const {
    std::optional<HitInfo> nearest;
    for (const auto& shape : _shapes) {
        std::optional<HitInfo> hit = shape->intersect(ray);
        if (hit && (!nearest || hit->t < nearest->t)) {
            nearest = hit;
        }
    }
    return nearest;
}
