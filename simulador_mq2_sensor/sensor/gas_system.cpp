// gas_system.cpp
#include "gas_system.hpp"
#include "application.hpp" // Para dt
#include <cmath>
#include <cstdlib>

// Función de mapeo (privada a este archivo)
namespace {
    float map(float value, float start1, float stop1, float start2, float stop2) {
        return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
    }
}

// --- Implementación de SmokeParticle ---
SmokeParticle::SmokeParticle(sf::Vector2f pos, float radius) {
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(pos.x + (rand() % 20 - 10), pos.y + (rand() % 20 - 10));
    shape.setFillColor(sf::Color(200, 200, 200, 60));

    float angle = map(rand() % 100, 0, 99, -180.0f, 0.0f);
    angle *= 3.14159f / 180.f;
    float speed = (rand() % 40) + 40.f;
    velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

    lifetime = map(rand() % 100, 0, 99, 1.525f, 3.025f);
    totalLifetime = lifetime;
}

void SmokeParticle::update(float deltaTime) {
    lifetime -= deltaTime;
    shape.move(velocity * deltaTime);
    float lifePercent = std::max(0.f, lifetime / totalLifetime);
    sf::Uint8 newAlpha = static_cast<sf::Uint8>(std::pow(lifePercent, 2) * 60);
    shape.setFillColor(sf::Color(200, 200, 200, newAlpha));
}


// --- Implementación de GasSystem ---
GasSystem::GasSystem() :
    m_spawnCounter(0.0f),
    m_maxParticlesPerSec(200.0f),
    m_gasSourcePos(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 50.f)
{
    // Inicializar el generador de números aleatorios
    srand(static_cast<unsigned>(time(0)));
}

void GasSystem::Update(bool isSpawning) {
    // 1. Generar nuevas partículas si se está "disparando"
    float spawnRateThisFrame = 0.0f;
    if (isSpawning) {
        spawnRateThisFrame = m_maxParticlesPerSec;
    }

    m_spawnCounter += spawnRateThisFrame * dt;
    while (m_spawnCounter >= 1.0f) {
        float radius = map(rand() % 100, 0, 99, 13.f, 23.f);
        m_particles.push_back(SmokeParticle(m_gasSourcePos, radius));
        m_spawnCounter -= 1.0f;
    }

    // 2. Actualizar y eliminar partículas muertas
    for (int i = m_particles.size() - 1; i >= 0; --i) {
        m_particles[i].update(dt);
        if (m_particles[i].lifetime <= 0) {
            m_particles.erase(m_particles.begin() + i);
        }
    }
}

void GasSystem::Render(sf::RenderWindow& window) {
    // Dibujar el humo con modo aditivo
    for (const auto& p : m_particles) {
        window.draw(p.shape, sf::BlendAdd);
    }
}