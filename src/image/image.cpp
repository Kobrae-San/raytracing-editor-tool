#include "image/image.h"

Image::Image(unsigned int width, unsigned int height)
    : _width(width), _height(height), _pixels(static_cast<std::size_t>(width) * height) {
}

unsigned int Image::width() const {
    return _width;
}

unsigned int Image::height() const {
    return _height;
}

void Image::setPixel(unsigned int x, unsigned int y, const Colour& colour) {
    _pixels[index(x, y)] = colour;
}

const Colour& Image::pixel(unsigned int x, unsigned int y) const {
    return _pixels[index(x, y)];
}

std::size_t Image::index(unsigned int x, unsigned int y) const {
    return static_cast<std::size_t>(y) * _width + x;
}
