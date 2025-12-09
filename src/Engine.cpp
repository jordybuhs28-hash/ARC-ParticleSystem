#include "Engine.hpp"
#include "Particle.hpp"
#include <cstdlib>

void Engine::input() {
    sf::Event event;
    while (m_Window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            m_Window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            
            // spawn 5 particles at mouse click
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            for (int i = 0; i < 5; i++) {
                int numPoints = 25 + rand() % 26; // random between 25–50
                Particle p(m_Window, numPoints, mousePos);
                m_particles.push_back(p);
            }
            std::cout << "Spawned particles at (" 
                      << mousePos.x << ", " << mousePos.y << ")" << std::endl;
        }
    }
}
