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
    sf::Vector2f center_;
    std::vector<sf::Vector2f> points_;
    sf::Color outerColor_;
    int numPoints_;

    sf::Vector2f velocity_;
    double ttl_;
    double rotationSpeed_;
    double shrinkRate_;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    static bool almostEqual(double a, double b, double eps = 1e-6);
};

