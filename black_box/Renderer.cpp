#include "Renderer.h"
#include "glfwWrapper.h"
#include <algorithm>
#include <cmath>

inline constexpr double maxZoom = 60.;
inline constexpr double initialZoom = 10;
inline constexpr double zoomCoef = 0.01;
inline constexpr double minScale = 0.005;

Renderer::Renderer(const char* name, unsigned int width, unsigned int height) {
    // enable antialiasing
    glfwWindowHint(GLFW_SAMPLES, 4);
    window = safeGLFWCall(
            glfwCreateWindow,
            int(width), int(height), name, nullptr, nullptr);
    safeGLFWCall(glfwMakeContextCurrent, window);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    zoomValue = initialZoom;
    updateScale();
}

bool Renderer::shouldClose() const {
    return glfwWindowShouldClose(window);
}

Renderer::~Renderer() {
    glfwDestroyWindow(window);
}

Painter Renderer::getPainter() {
    return {window, view};
}

GLFWwindow *Renderer::context() {
    return window;
}

void Renderer::onZoom(double step) {
    zoomValue = std::clamp(zoomValue + step, 1., maxZoom);
    updateScale();
}

void Renderer::updateScale() {
    view.scale = std::exp(zoomValue * zoomCoef) - 1. + minScale;
}
