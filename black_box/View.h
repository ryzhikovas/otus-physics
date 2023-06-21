#pragma once
#include "../Point.h"

struct View {
    Point viewPoint{0, 0};
    double scale{0.1};
    Point toPixel(const Point& worldPos) const;
};
