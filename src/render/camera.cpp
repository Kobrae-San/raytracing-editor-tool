#include "render/camera.h"

Camera::Camera(const Vector& position)
    : _position(position) {
}

const Vector& Camera::position() const {
    return _position;
}

Ray Camera::rayThroughPixel(unsigned int pixelX, unsigned int pixelY,
                             unsigned int imageWidth, unsigned int imageHeight,
                             double screenWidth) const {
    // The screen plane keeps the image's aspect ratio.
    double screenHeight = screenWidth * imageHeight / imageWidth;

    // Distance of the pixel from the centre pixel, scaled from pixel units
    // to screen units. y is inverted because pixel rows grow downward while
    // the screen's y axis grows upward.
    double x = (pixelX - (imageWidth - 1) / 2.0) * (screenWidth / imageWidth);
    double y = ((imageHeight - 1) / 2.0 - pixelY) * (screenHeight / imageHeight);

    // The camera always faces the positive Z-axis for now, so the screen
    // plane sits one unit in front of it.
    Vector direction(x, y, 1.0);

    return Ray(_position, direction);
}

Colour Camera::trace(const Ray& ray, const Sphere& sphere, const Light& light) const {
    auto hit = sphere.intersect(ray);
    if (!hit) {
        return Colour(0.0, 0.0, 0.0);
    }

    return hit->material->shade(*hit, light);
}
