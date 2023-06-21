#pragma once
#include "../Point.h"
#include "View.h"

class Screen {
public:
    Screen() = default;
    Screen(View view, int screenWidth, int screenHeight);
    Point toScreen(const Point& worldPos) const;
private:
    double xRes{};
    double yRes{};
    View view;
};
