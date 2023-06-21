#pragma once
#include "GLFW/glfw3.h"
#include "View.h"
#include "Screen.h"
#include "../Color.h"

class PainterImpl {
public:
    PainterImpl(GLFWwindow* window, const View& view);
    ~PainterImpl();
    void draw(const Point& center, double radius, const Color& color);
    void draw(const Point& topLeft, const Point& bottomRight, const Color& color);
private:
    void addVertex(const Point& pos);
private:
    GLFWwindow* window;
    Screen screen;
};
