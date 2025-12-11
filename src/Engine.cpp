#include "Engine.hpp"
#include "Particle.hpp"
#include <iostream>
#include <cstdlib>
#include <algorithm>


Engine::Engine(unsigned width, unsigned height)
    : m_Window(sf::VideoMode(width, height), "ARC Particle System") {
    m_Window.setFramerateLimit(60);


    // Run unit tests once at startup
    {
        sf::Vector2i centerPix(m_Window.getSize().x / 2, m_Window.getSize().y / 2);
        Particle test(m_Window, 12, centerPix);
        std::cout << "[Tests] Starting unit tests..." << std::endl;
        test.unitTests();
        std::cout << "[Tests] Done." << std::endl;
    }
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


        // Left click spawns particles
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);


            // Spawn a handful of particles at click
            for (int i = 0; i < 5; ++i) {
                int numPoints = 25 + (std::rand() % 26); // 25–50 points
                m_particles.emplace_back(m_Window, numPoints, mousePos);
            }
        }
    }
}


void Engine::update(double dt) {
    std::vector<Particle> newParticles;


    for (auto& p : m_particles) {
        p.update(dt, m_Window);


        // If you’ve added fractal bursts:
        // if (p.hasBurst()) {
        //     auto children = p.burst(m_Window);
        //     newParticles.insert(newParticles.end(), children.begin(), children.end());
        // }
    }


    // Add any new burst particles
    m_particles.insert(m_particles.end(), newParticles.begin(), newParticles.end());


    // Remove dead particles
    m_particles.erase(
        std::remove_if(m_particles.begin(), m_particles.end(),
                       [](const Particle& p) { return p.isDead(); }),
        m_particles.end()
    );
}


void Engine::draw() {
    m_Window.clear(sf::Color(20, 20, 24));


    // Draw all particles
    for (const auto& p : m_particles) {
        m_Window.draw(p);
    }


    m_Window.display();
}

