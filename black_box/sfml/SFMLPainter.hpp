#pragma once
#include "../../Painter.hpp"
#include "View.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf {
    class RenderWindow;
}

class SFMLPainter : public Painter {
  public:
    SFMLPainter(sf::RenderWindow& window, const View& view);
    ~SFMLPainter() override;
    void draw(const Point& center, double radius, const Color& color) override;
    void draw(const Point& topLeft, const Point& bottomRight,
              const Color& color) override;

  private:
    sf::Color toSFMLColor(const Color& color) const;
    sf::Vector2f toVector(const Point& point) const;

  private:
    sf::RenderWindow& window;
    const View& view;
};
