#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>


class Particle : public sf::Drawable {
public:
    Particle(sf::RenderWindow& window, int numPoints, sf::Vector2i mousePix);


    void update(double dt, sf::RenderWindow& window);
    bool isDead() const;
    void unitTests();


private:
    // Geometry
    sf::Vector2f center_;
    std::vector<sf::Vector2f> points_;
    sf::Color outerColor_;
    int numPoints_;


    // Motion
    sf::Vector2f velocity_;
    double ttl_;
    double rotationSpeed_;
    double shrinkRate_;

    // Orbiting
    bool orbiting_ = false;          // flag to enable orbit
    float orbitRadius_ = 0.0f;       // distance from orbit center
    float orbitAngle_ = 0.0f;        // current angle in radians
    float orbitAngularSpeed_ = 0.0f; // radians per second
    sf::Vector2f orbitCenter_;       // point to orbit around


    // Constants
    static constexpr float GRAVITY = 300.0f;       // pixels/sec^2
    static constexpr float S_AMPLITUDE = 100.0f;   // horizontal sway strength
    static constexpr float S_FREQUENCY = 0.02f;    // controls S curve tightness
    static constexpr float MAX_TTL = 10.0f;        // extended lifetime for visibility


    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    static bool almostEqual(double a, double b, double eps = 1e-6);
};
