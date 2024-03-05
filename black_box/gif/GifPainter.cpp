#include "GifPainter.hpp"
#include <map>

GifPainter::GifPainter(Image& image, Point offset, double scale)
    : image{image}, offset{offset}, scale{scale} {
    image.fill(Color(0.0, 0.0, 0.0), 0.);
}

void GifPainter::draw(const Point& center, double radius, const Color& color) {
    const int intRadius = std::round(radius * scale);

    static std::map<int, Image> renderedCircles;

    auto iter = renderedCircles.find(intRadius);

    if (iter == renderedCircles.end()) {
        Image circle(intRadius * 2 + 1, intRadius * 2 + 1);
        circle.fill(color, 1.);
        Point localCenter(intRadius, intRadius);
        const int radius2 = intRadius * intRadius;

        for (size_t i = 0; i < circle.height(); ++i) {
            for (size_t j = 0; j < circle.width(); ++j) {
                if (distance2(localCenter, Point(j, i)) < radius2) {
                    circle.setPixel(j, i, color);
                }
            }
        }
        iter = renderedCircles.emplace(intRadius, circle).first;
    }
    const Image& circle = iter->second;
    const Point imagePoint = center * scale + offset;
    image.put(imagePoint.x - intRadius,
              image.height() - (imagePoint.y + intRadius), circle);
}

void GifPainter::draw(const Point& topLeft, const Point& bottomRight,
                      const Color& color) {
    const size_t width = (bottomRight.x - topLeft.x) * scale;
    const size_t height = (bottomRight.y - topLeft.y) * scale;
    static Image renderedRect(width, height);
    renderedRect.fill(color, 0.);
    const Point imagePoint = topLeft * scale + offset;
    image.put(imagePoint.x, imagePoint.y, renderedRect);
}
