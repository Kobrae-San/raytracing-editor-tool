#pragma once

#include "colour/colour.h"
#include "geometry/sphere.h"
#include "math/ray.h"
#include "math/vector.h"
#include "scene/light.h"

// A camera: a point in the scene that rays are shot from. For now it always
// faces the positive Z-axis; a direction will be added later.
class Camera {
public:
    Camera(const Vector& position);

    // Read-only access to the position.
    const Vector& position() const;

    // The ray that leaves the camera and passes through the centre of the
    // screen for pixel (pixelX, pixelY) of an image of imageWidth by
    // imageHeight pixels, mapped onto a screen plane screenWidth units wide
    // (screen height follows the image's aspect ratio).
    Ray rayThroughPixel(unsigned int pixelX, unsigned int pixelY,
                         unsigned int imageWidth, unsigned int imageHeight,
                         double screenWidth) const;

    // The colour seen along ray: the sphere's material's shaded colour,
    // lit by light, if the ray hits it, black otherwise.
    Colour trace(const Ray& ray, const Sphere& sphere, const Light& light) const;

private:
    Vector _position;
};
