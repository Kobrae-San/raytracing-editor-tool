#include "render/trace.h"

#include "material/material.h"

Colour trace(const Ray& ray, const Scene& scene) {
    std::optional<HitInfo> hit = scene.nearestHit(ray);
    if (!hit) {
        return Colour(0, 0, 0);
    }
    return hit->material->shade(*hit, scene.toLight());
}
