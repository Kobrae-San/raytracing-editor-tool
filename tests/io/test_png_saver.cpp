#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <vector>

#include "io/png_saver.h"
#include "lodepng.h"

TEST_CASE("PngSaver writes every pixel, row by row", "[png]") {
    Image image(2, 2);
    image.setPixel(1, 0, Colour(1, 0.5, 0));

    std::string path = (std::filesystem::temp_directory_path() / "rt_test_png_saver.png").string();
    PngSaver().save(image, path);

    std::vector<unsigned char> bytes;
    unsigned int width = 0;
    unsigned int height = 0;
    REQUIRE(lodepng::decode(bytes, width, height, path, LCT_RGB) == 0);
    std::filesystem::remove(path);

    REQUIRE(width == 2);
    REQUIRE(height == 2);
    // 0.5 * 255 = 127.5, rounded to the nearest byte: 128.
    std::vector<int> expected = {0, 0, 0, 255, 128, 0, 0, 0, 0, 0, 0, 0};
    REQUIRE(std::vector<int>(bytes.begin(), bytes.end()) == expected);
}

TEST_CASE("PngSaver throws when the file cannot be written", "[png]") {
    Image image(1, 1);

    REQUIRE_THROWS_AS(PngSaver().save(image, "/no/such/folder/image.png"), std::runtime_error);
}
