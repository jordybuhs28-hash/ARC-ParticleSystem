#include "Engine.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>

Engine::Engine(unsigned width, unsigned height)
    : m_Window(sf::VideoMode(width, height), "ARC Particle System") {
    m_Window.setFramerateLimit(60);
}

void Engine::run() {
    // Unit tests at startup
    {
        sf::Vector2i centerPix(m_Window.getSize().x / 2, m_Window.getSize().y / 2);
        Particle test(m_Window, 12, centerPix);
        std::cout << "[Tests] Starting unit tests..." << std::endl;
        test.unitTests();
        std::cout << "[Tests] Done." << std::endl;
    }

    while (m_Window.isOpen()) {
        double dt = m_Clock.restart().asSeconds();
        input();
        update(dt);
        draw();
    }
}

void Engine::input() {
    sf::Event event;
    while (m_Window.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            m_Window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {

            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            std::cout << "[Input] Click at (" << mousePos.x << ", " << mousePos.y << ")\n";

            // Spawn multiple particles per click
            for (int i = 0; i < 5; ++i) {
                int numPoints = 25 + (std::rand() % 26); // 25–50 points
                m_particles.emplace_back(m_Window, numPoints, mousePos);
            }
        }
    }
}

void Engine::update(double dt) {
    // Advance each particle
    for (auto& p : m_particles) {
        p.update(dt, m_Window);
    }

    // Remove expired particles
    m_particles.erase(
        std::remove_if(m_particles.begin(), m_particles.end(),
                       [](const Particle& p) { return p.isDead(); }),
        m_particles.end()
    );
}

void Engine::draw() {
    m_Window.clear(sf::Color(20, 20, 24)); // subtle dark background
    for (const auto& p : m_particles) {
        m_Window.draw(p);
    }
    m_Window.display();
}