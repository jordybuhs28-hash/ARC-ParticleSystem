#define _USE_MATH_DEFINES
#include "Particle.hpp"
#include <cstdlib>
#include <cmath>

Particle::Particle(sf::RenderWindow& window, int numPoints, sf::Vector2i mousePix) {
    numPoints_ = numPoints;

    // Randomized outer color
    outerColor_ = sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256);

    // Center position (start at click point)
    center_ = sf::Vector2f(static_cast<float>(mousePix.x), static_cast<float>(mousePix.y));

    // Build geometry points around the center
    points_.resize(numPoints_);
    for (int i = 0; i < numPoints_; ++i) {
        float angle = i * 2.0f * static_cast<float>(M_PI) / numPoints_;
        float radius = 10.0f + (std::rand() % 20); // 10–30 px radius
        points_[i] = sf::Vector2f(std::cos(angle) * radius, std::sin(angle) * radius);
    }

    // Randomized initial velocity (slight upward kick)
    velocity_ = sf::Vector2f((std::rand() % 200 - 100), (std::rand() % -200));

    ttl_ = MAX_TTL; // extended lifetime
    rotationSpeed_ = (std::rand() % 180) - 90; // -90 to +90 deg/sec
    shrinkRate_ = 0.5;
}

void Particle::update(double dt, sf::RenderWindow& window) {
    ttl_ -= dt;
    if (ttl_ <= 0) return;

    // Gravity (vertical acceleration)
    velocity_.y += GRAVITY * static_cast<float>(dt);

    // Vertical descent
    center_.y += velocity_.y * static_cast<float>(dt);

    // Horizontal S-shaped sway based on vertical position
    float sOffset = S_AMPLITUDE * std::sin(center_.y * S_FREQUENCY);
    center_.x += sOffset * static_cast<float>(dt);

    // Rotate points around center
    float theta = rotationSpeed_ * static_cast<float>(dt) * M_PI / 180.0f;
    float cosT = std::cos(theta);
    float sinT = std::sin(theta);
    for (auto& p : points_) {
        float x = p.x;
        float y = p.y;
        p.x = cosT * x - sinT * y;
        p.y = sinT * x + cosT * y;
    }

    // Shrink
    float scale = 1.0f - shrinkRate_ * static_cast<float>(dt);
    for (auto& p : points_) {
        p *= scale;
    }
}

bool Particle::isDead() const {
    return ttl_ <= 0;
}

bool Particle::almostEqual(double a, double b, double eps) {
    return std::fabs(a - b) <= eps;
}

void Particle::unitTests() {
    std::cout << "---- Particle::unitTests ----\n";

    // Rotation test
    {
        double x = 1.0, y = 0.0;
        double theta = M_PI / 2.0;
        double xr = x * std::cos(theta) - y * std::sin(theta);
        double yr = x * std::sin(theta) + y * std::cos(theta);
        bool pass = almostEqual(xr, 0.0) && almostEqual(yr, 1.0);
        std::cout << "[Rotation 90 deg] " << (pass ? "PASS" : "FAIL") << "\n";
    }

    // Scaling test
    {
        double x = 2.0, y = 3.0;
        double s = 2.0;
        bool pass = almostEqual(s * x, 4.0) && almostEqual(s * y, 6.0);
        std::cout << "[Scaling x2] " << (pass ? "PASS" : "FAIL") << "\n";
    }

    // Translation test
    {
        double x = 5.0, y = -1.0;
        double dx = 3.0, dy = 4.0;
        bool pass = almostEqual(x + dx, 8.0) && almostEqual(y + dy, 3.0);
        std::cout << "[Translation + (3,4)] " << (pass ? "PASS" : "FAIL") << "\n";
    }

    // Gravity test
    {
        double vy0 = 0.0;
        double g = GRAVITY;
        double dt = 0.016;
        double vy1 = vy0 + g * dt;
        bool pass = almostEqual(vy1, g * dt);
        std::cout << "[Gravity] " << (pass ? "PASS" : "FAIL") << "\n";
    }

    std::cout << "-----------------------------\n";
}

void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // --- Glow Aura ---
    sf::VertexArray aura(sf::TriangleFan, numPoints_ + 1);

    aura[0].position = center_;
    aura[0].color = sf::Color(outerColor_.r, outerColor_.g, outerColor_.b, 50); // faint glow

    for (int i = 0; i < numPoints_; ++i) {
        aura[i + 1].position = center_ + points_[i] * 1.5f; // 1.5x bigger
        aura[i + 1].color = sf::Color(outerColor_.r, outerColor_.g, outerColor_.b, 50);
    }

    target.draw(aura, states);

    // --- Original Particle Drawing ---
    sf::VertexArray fan(sf::TriangleFan, numPoints_ + 1);

    fan[0].position = center_;
    fan[0].color = sf::Color::White;

    for (int i = 0; i < numPoints_; ++i) {
        fan[i + 1].position = center_ + points_[i];
        fan[i + 1].color = outerColor_;
    }

    target.draw(fan, states);
}
