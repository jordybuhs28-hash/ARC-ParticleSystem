#include "Engine.hpp"
#include "Particle.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>

Particle::ShapeType currentShape = Particle::ShapeType::RandomPolygon;

Engine::Engine(unsigned width, unsigned height)
    : m_Window(sf::VideoMode(width, height), "Interactive Particle System") {
    m_Window.setFramerateLimit(60);
}

void Engine::run() {
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

        // Switch shape modes
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::C) currentShape = Particle::ShapeType::Circle;
            if (event.key.code == sf::Keyboard::S) currentShape = Particle::ShapeType::Square;
            if (event.key.code == sf::Keyboard::R) currentShape = Particle::ShapeType::RandomPolygon;
        }

        // Left click spawns multiple shapes
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

            // Spawn 3 different shapes at once
            m_particles.emplace_back(m_Window, 30, mousePos, Particle::ShapeType::Circle);
            m_particles.emplace_back(m_Window, 4, mousePos, Particle::ShapeType::Square);
            int numPoints = 25 + (std::rand() % 26);
            m_particles.emplace_back(m_Window, numPoints, mousePos, Particle::ShapeType::RandomPolygon);

            // Also spawn a burst of the currently selected shape
            for (int i = 0; i < 5; ++i) {
                int numPoints2 = 12 + (std::rand() % 12);
                m_particles.emplace_back(m_Window, numPoints2, mousePos, currentShape);
            }
        }
    }
}

void Engine::update(double dt) {
    for (auto& p : m_particles) {
        p.update(dt, m_Window);
    }

    // Remove dead particles
    m_particles.erase(
        std::remove_if(m_particles.begin(), m_particles.end(),
                       [](const Particle& p) { return p.isDead(); }),
        m_particles.end()
    );
}

void Engine::draw() {
    m_Window.clear(sf::Color(20, 20, 24));

    for (const auto& p : m_particles) {
        m_Window.draw(p);
    }

    m_Window.display();
}
