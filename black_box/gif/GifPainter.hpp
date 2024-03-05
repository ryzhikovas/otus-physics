#pragma once
#include "../../Painter.hpp"
#include "Image.hpp"

class GifPainter : public Painter {
  public:
    GifPainter(Image& image, Point offset, double scale);
    void draw(const Point& center, double radius, const Color& color) override;
    void draw(const Point& topLeft, const Point& bottomRight,
              const Color& color) override;

  private:
    Image& image;
    Point offset;
    double scale;
};
