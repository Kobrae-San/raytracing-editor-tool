#pragma once

#include <string>

#include "image/image.h"

// Strategy interface for saving an image. Callers depend on "a saver", not on
// a file format or a library, so adding a format (e.g. EXR) is one new class.
//
// Contract every implementation must keep (Liskov): write the whole image to
// path, or throw std::runtime_error. The image is never modified.
class ImageSaver {
public:
    virtual ~ImageSaver() = default;

    virtual void save(const Image& image, const std::string& path) const = 0;
};
