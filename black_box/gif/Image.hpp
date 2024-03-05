#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
#include "../../Color.hpp"

class Image {
  public:
    Image(size_t width, size_t height);
    void setPixel(size_t x, size_t y, const Color& color, double alpha = 0.);
    void put(int xPos, int yPos, const Image& source);
    void fill(const Color& color, double alpha);
    size_t width() const;
    size_t height() const;
    const uint8_t* data() const;
  private:
    ptrdiff_t offsetToPixel(size_t x, size_t y) const;
    ptrdiff_t step() const;
  private:
    size_t width_;
    size_t height_;
    std::vector<uint8_t> buffer;
};
