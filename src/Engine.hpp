#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Particle.hpp"

class Engine {
public:
    Engine(unsigned width, unsigned height);
    void run();

private:
    sf::RenderWindow m_Window;
    sf::Clock m_Clock;
    std::vector<Particle> m_particles;

    void input();
    void update(double dt);
    void draw();
};

