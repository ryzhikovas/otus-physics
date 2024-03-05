#include "Image.hpp"
#include <algorithm>

// Каждый пиксель состоит из четырех байт (формат RGBA8)
constexpr size_t channels = 4;

Image::Image(size_t width, size_t height) : width_{width}, height_{height} {
    // Буфер под width x height пикселей
    buffer.resize(width * height * channels);
}

void Image::setPixel(size_t x, size_t y, const Color& color, double alpha) {
    uint8_t* pixel = buffer.data() + offsetToPixel(x, y);
    *pixel++ = uint8_t(color.red() * 255);
    *pixel++ = uint8_t(color.green() * 255);
    *pixel++ = uint8_t(color.blue() * 255);
    *pixel = uint8_t(alpha * 255);
}

void Image::put(int xPos, int yPos, const Image& source) {
    const size_t srcX = std::max(0, -xPos);
    const size_t srcY = std::max(0, -yPos);
    const size_t trgX = std::max(0, xPos);
    const size_t trgY = std::max(0, yPos);

    if (srcX < source.width() && srcY < source.height() && trgX < width() &&
        trgY < height()) {
        const size_t w = std::min(source.width() - srcX, width() - trgX);
        const size_t h = std::min(source.height() - srcY, height() - trgY);
        ptrdiff_t srcOffset = source.offsetToPixel(srcX, srcY);
        ptrdiff_t trgOffset = offsetToPixel(trgX, trgY);

        for (size_t y = 0; y < h; ++y) {
            auto src = source.buffer.begin() + srcOffset;
            auto dst = buffer.begin() + trgOffset;
            for (size_t x = 0; x < w; ++x) {
                const uint8_t alpha = *std::next(src, channels - 1);

                if (alpha != 255) {
                    for (size_t channel = 0; channel < channels; ++channel) {
                        *dst = *src;
                        ++dst;
                        ++src;
                    }
                } else {
                    dst += channels;
                    src += channels;
                }
            }
            /*std::copy_n(source.buffer.begin() + srcOffset,
                        w * channels,
                        buffer.begin() + trgOffset);*/
            srcOffset += source.step();
            trgOffset += step();
        }
    }
}

size_t Image::width() const {
    return width_;
}

size_t Image::height() const {
    return height_;
}

const uint8_t* Image::data() const {
    return buffer.data();
}

ptrdiff_t Image::offsetToPixel(size_t x, size_t y) const {
    return (y * width() + x) * channels;
}

ptrdiff_t Image::step() const {
    return width() * channels;
}

void Image::fill(const Color& color, double alpha) {
    for (size_t y = 0; y < height(); ++y) {
        for (size_t x = 0; x < width(); ++x) {
            setPixel(x, y, color, alpha);
        }
    }
}
