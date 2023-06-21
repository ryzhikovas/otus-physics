#pragma once
#include <memory>
#include "Point.h"
#include "Color.h"

struct GLFWwindow;
struct View;
class PainterImpl;

class Painter {
public:
    Painter(GLFWwindow* window, const View& view);
    ~Painter();
    /**
     * Рисует круг цвета color
     * @param center центр круга
     * @param radius радиус круга
     * @param color цвет заливки
     */
    void draw(const Point& center, double radius, const Color& color);
    /**
     * Рисует прямоугольник цвета color
     * @param topLeft координата верхнего левого угла
     * @param bottomRight координата нижнего правого угла
     * @param color цвет заливки
     */
    void draw(const Point& topLeft, const Point& bottomRight, const Color& color);
private:
    std::unique_ptr<PainterImpl> impl;
};