#pragma once
#include "GLFW/glfw3.h"
#include "../Painter.h"
#include "View.h"
#include "Zoomable.h"


class Renderer: public Zoomable {
public:
    Renderer(const char* name = "Collider", unsigned width = 1280, unsigned height = 960);
    ~Renderer();
    bool shouldClose() const;
    Painter getPainter();
    GLFWwindow* context();
    void onZoom(double step) override;
private:
    void updateScale();
private:
    GLFWwindow* window;
    View view;
    double zoomValue;
};
