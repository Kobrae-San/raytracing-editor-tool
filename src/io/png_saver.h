#pragma once

#include "io/image_saver.h"

// Saves an image as a PNG file to disk, using the LodePNG library.
class PngSaver : public ImageSaver {
public:
    void save(Image& image, const std::string& path) override;
};
