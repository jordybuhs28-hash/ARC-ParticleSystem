#pragma once
#include <SFML/Graphics.hpp>

class CartesianPlane {
public:
    CartesianPlane(int width = 0, int height = 0);

    void setSize(int width, int height);

    sf::Vector2f toCartesian(const sf::Vector2i& pixel) const;
    sf::Vector2i toPixel(const sf::Vector2f& cartesian) const;

private:
    int width_, height_;
};
