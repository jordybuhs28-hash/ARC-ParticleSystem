#include "CartesianPlane.hpp"

CartesianPlane::CartesianPlane(int width, int height)
    : width_(width), height_(height) {}

void CartesianPlane::setSize(int width, int height) {
    width_ = width;
    height_ = height;
}

sf::Vector2f CartesianPlane::toCartesian(const sf::Vector2i& pixel) const {
    float x = pixel.x - width_ / 2.0f;
    float y = height_ / 2.0f - pixel.y;
    return sf::Vector2f(x, y);
}

sf::Vector2i CartesianPlane::toPixel(const sf::Vector2f& cartesian) const {
    int x = static_cast<int>(cartesian.x + width_ / 2.0f);
    int y = static_cast<int>(height_ / 2.0f - cartesian.y);
    return sf::Vector2i(x, y);
}
