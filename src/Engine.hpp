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

    // Core loop methods
    void input();              // handle events
    void update(double dt);    // advance particles
    void draw();               // render particles
};
