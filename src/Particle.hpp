#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>

class Particle : public sf::Drawable {
public:
    enum class ShapeType { Circle, Square, RandomPolygon };

    Particle(sf::RenderWindow& window, int numPoints, sf::Vector2i mousePix, ShapeType shape);

    void update(double dt, sf::RenderWindow& window);
    bool isDead() const;
    void unitTests();

private:
    // Geometry
    sf::Vector2f center_;
    std::vector<sf::Vector2f> points_;
    sf::Color outerColor_;
    int numPoints_;
    ShapeType shapeType_;

    // Motion
    sf::Vector2f velocity_;
    double ttl_;
    double rotationSpeed_;
    double shrinkRate_;

    // Constants
    static constexpr float GRAVITY = 300.0f;
    static constexpr float S_AMPLITUDE = 100.0f;
    static constexpr float S_FREQUENCY = 0.02f;
    static constexpr float MAX_TTL = 10.0f;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    static bool almostEqual(double a, double b, double eps = 1e-6);
};
