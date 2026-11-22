#pragma once

#include "image/image.h"
#include "math/ray.h"
#include "math/vector.h"
#include "scene/scene.h"

// A pinhole camera: an eye and a screen. For each pixel, it sends a ray from
// the eye through the centre of that pixel on the screen. The screen faces
// the z axis for now (x right, y up, z forward, see ADR 0009).
class Camera {
public:
    Camera(const Vector& eye, const Vector& screenCentre, double screenWidth);

    const Vector& eye() const;

    // The ray through the centre of pixel (column, row) of a width x height
    // image, counted from the top-left corner. The screen's height follows
    // the image's aspect ratio. The direction is not normalised.
    Ray rayThroughPixel(unsigned int column, unsigned int row,
                        unsigned int width, unsigned int height) const;

    // One traced ray per pixel.
    Image render(const Scene& scene, unsigned int width, unsigned int height) const;

private:
    Vector _eye;
    Vector _screenCentre;
    double _screenWidth;
};
