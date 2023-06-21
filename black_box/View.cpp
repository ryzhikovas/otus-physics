#include "View.h"

Point View::toPixel(const Point& worldPos) const {
    return (worldPos - viewPoint) * scale;
}