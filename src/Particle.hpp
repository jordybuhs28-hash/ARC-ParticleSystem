#pragma once
#include <SFML/Graphics.hpp>
#include "Matrix.hpp"
#include "RotationMatrix.hpp"
#include "ScalingMatrix.hpp"
#include "TranslationMatrix.hpp"
#include "CartesianPlane.hpp"
#include <cmath>
#include <iostream>

// Global constants
constexpr double PI      = 3.14159265358979323846;
constexpr double TTL     = 5.0;     // particle lifetime in seconds
constexpr double SCALE   = 0.999;   // shrink factor per frame
constexpr double GRAVITY = 9.8;     // gravity acceleration (pixels/sec^2)

class Particle : public sf::Drawable {
public:
    // Constructor: builds a particle with numPoints vertices at mouse click position
    Particle(const sf::RenderTarget& target, int numPoints, const sf::Vector2i& mousePix);

    // Update particle state each frame
    void update(double dt, const sf::RenderTarget& target);

    // Check if particle has expired
    bool isDead() const { return ttl_ <= 0.0; }

    // Transformations
    void rotate(double radians);
    void scale(double factor);
    void translate(double dx, double dy);

    // Testing helpers
    static bool almostEqual(double a, double b, double eps = 1e-9);
    void unitTests();

private:
    // Geometry
    Matrix A_;                // vertex matrix
    int n_;                   // number of vertices

    // Motion
    double radiansPerSec_;    // angular velocity
    double vx_, vy_;          // horizontal & vertical velocity
    double ttl_;              // time to live
    double gravity_;          // per-particle gravity constant

    // Positioning
    sf::Vector2f center_;     // center in Cartesian coords
    CartesianPlane plane_;    // maps Cartesian <-> pixel

    // Colors
    sf::Color baseColor_, edgeColor_;

    // Shape mode (extra credit: circle, starburst, spiral)
    int shapeMode_;

    // Drawing
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Shape generators (extra credit)
    void generateCircleLike(const sf::Vector2f& center);
    void generateStarburst(const sf::Vector2f& center);
    void generateSpiral(const sf::Vector2f& center);
};
