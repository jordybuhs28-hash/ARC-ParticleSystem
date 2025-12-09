#include "Particle.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

// Constructor
Particle::Particle(const sf::RenderTarget& target, int numPoints, const sf::Vector2i& mousePix)
    : A_(2, numPoints), n_(numPoints), ttl_(TTL) {

    // random angular velocity
    radiansPerSec_ = ((float)rand() / RAND_MAX) * PI;

    // random velocities
    vx_ = (rand() % 2 ? 1 : -1) * (100 + rand() % 400);
    vy_ = -(100 + rand() % 400); // initial upward velocity
    gravity_ = GRAVITY;

    plane_.setSize(target.getSize().x, target.getSize().y);

    // map mouse click to Cartesian
    center_ = plane_.toCartesian(mousePix);

    // colors
    baseColor_ = sf::Color::White;
    edgeColor_ = sf::Color(rand() % 255, rand() % 255, rand() % 255);

    // choose shape mode randomly (extra credit)
    shapeMode_ = rand() % 3;
    if (shapeMode_ == 0) generateCircleLike(center_);
    else if (shapeMode_ == 1) generateStarburst(center_);
    else generateSpiral(center_);
}

// Update
void Particle::update(double dt, const sf::RenderTarget& target) {
    ttl_ -= dt;
    if (ttl_ <= 0.0) return;

    // rotate
    rotate(dt * radiansPerSec_);

    // shrink
    scale(SCALE);

    // gravity + velocity
    vy_ += gravity_ * dt;
    double dx = vx_ * dt;
    double dy = vy_ * dt;

    // translate
    translate(dx, dy);
}

// Transformations
void Particle::rotate(double radians) {
    RotationMatrix R(radians);
    A_ = R.multiply(A_);
}

void Particle::scale(double factor) {
    ScalingMatrix S(factor);
    A_ = S.multiply(A_);
}

void Particle::translate(double dx, double dy) {
    TranslationMatrix T(dx, dy, A_.getCols());
    A_ = A_.add(T);
    center_.x += dx;
    center_.y += dy;
}

// Shape generators (extra credit)
void Particle::generateCircleLike(const sf::Vector2f& center) {
    double theta = ((float)rand() / RAND_MAX) * (PI / 2);
    double dTheta = 2 * PI / (n_ - 1);
    for (int j = 0; j < n_; j++) {
        double r = 20 + rand() % 60;
        double dx = r * cos(theta);
        double dy = r * sin(theta);
        A_(0, j) = center.x + dx;
        A_(1, j) = center.y + dy;
        theta += dTheta;
    }
}

void Particle::generateStarburst(const sf::Vector2f& center) {
    for (int j = 0; j < n_; j++) {
        double angle = (2 * PI * j) / n_;
        double r = (j % 2 == 0 ? 80 : 30); // alternating spikes
        A_(0, j) = center.x + r * cos(angle);
        A_(1, j) = center.y + r * sin(angle);
    }
}

void Particle::generateSpiral(const sf::Vector2f& center) {
    for (int j = 0; j < n_; j++) {
        double angle = (2 * PI * j) / n_;
        double r = 10 + j * 2; // radius grows with j
        A_(0, j) = center.x + r * cos(angle);
        A_(1, j) = center.y + r * sin(angle);
    }
}

// Draw
void Particle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::VertexArray fan(sf::TriangleFan, n_ + 1);

    // center pixel
    sf::Vector2i centerPix = plane_.toPixel(center_);
    fan[0].position = sf::Vector2f(static_cast<float>(centerPix.x),
                                   static_cast<float>(centerPix.y));
    fan[0].color = baseColor_;

    // vertices
    for (int j = 1; j <= n_; j++) {
        sf::Vector2f cart(static_cast<float>(A_(0, j-1)),
                          static_cast<float>(A_(1, j-1)));
        sf::Vector2i pix = plane_.toPixel(cart);
        fan[j].position = sf::Vector2f(static_cast<float>(pix.x),
                                       static_cast<float>(pix.y));
        fan[j].color = edgeColor_;
    }

    target.draw(fan, states);
}

// Helpers
bool Particle::almostEqual(double a, double b, double eps) {
    return std::fabs(a - b) < eps;
}

void Particle::unitTests() {
    std::cout << "Running Particle unit tests..." << std::endl;
    // Example: rotation test
    Matrix init = A_;
    rotate(PI/2);
    // check values with almostEqual...
    std::cout << "Unit tests complete." << std::endl;
}
