#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include <vector>

class Engine {
public:
    Engine(int width, int height);
    void run();

private:
    sf::RenderWindow window_;
    std::vector<Particle> particles_;

    void processEvents();
    void update(double dt);
    void render();
};
