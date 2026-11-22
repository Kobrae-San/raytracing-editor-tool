#include "render/camera.h"

#include "render/trace.h"

Camera::Camera(const Vector& eye, const Vector& screenCentre, double screenWidth)
    : _eye(eye), _screenCentre(screenCentre), _screenWidth(screenWidth) {
}

const Vector& Camera::eye() const {
    return _eye;
}

Ray Camera::rayThroughPixel(unsigned int column, unsigned int row,
                            unsigned int width, unsigned int height) const {
    double pixelSize = _screenWidth / width;
    // + 0.5: the centre of the pixel. y is flipped: rows grow downward, the
    // world's y axis grows upward. 2.0, not 2: 5 / 2 is 2 in C++.
    double x = (column + 0.5 - width / 2.0) * pixelSize;
    double y = (height / 2.0 - row - 0.5) * pixelSize;
    Vector pixelCentre = _screenCentre + Vector(x, y, 0);
    return Ray(_eye, pixelCentre - _eye);
}

Image Camera::render(const Scene& scene, unsigned int width, unsigned int height) const {
    Image image(width, height);
    for (unsigned int row = 0; row < height; ++row) {
        for (unsigned int column = 0; column < width; ++column) {
            Ray ray = rayThroughPixel(column, row, width, height);
            image.setPixel(column, row, trace(ray, scene));
        }
    }
    return image;
}
