#include "Screen.h"

Screen::Screen(View view, int screenWidth, int screenHeight)
        : view{view},
          xRes{screenWidth / 2.},
          yRes{screenHeight / 2.} {
}

Point Screen::toScreen(const Point& worldPos) const {
    const Point pixel = view.toPixel(worldPos);
    auto toScreen = [] (double pix, double resolution) {
        return pix / resolution;
    };
    return {
            toScreen(pixel.x, xRes),
            toScreen(pixel.y, yRes),
    };
}
