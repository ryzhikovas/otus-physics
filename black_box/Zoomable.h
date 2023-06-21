#pragma once

class Zoomable {
public:
    virtual ~Zoomable() = default;
    virtual void onZoom(double step) = 0;
};
