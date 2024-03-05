#pragma once
#include "Color.hpp"
#include "Point.hpp"

class Painter {
  public:
    virtual ~Painter() = default;
    /**
     * Рисует круг цвета color
     * @param center центр круга
     * @param radius радиус круга
     * @param color цвет заливки
     */
    virtual void draw(const Point& center, double radius,
                      const Color& color) = 0;
    /**
     * Рисует прямоугольник цвета color
     * @param topLeft координата верхнего левого угла
     * @param bottomRight координата нижнего правого угла
     * @param color цвет заливки
     */
    virtual void draw(const Point& topLeft, const Point& bottomRight,
                      const Color& color) = 0;
};