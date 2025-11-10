// gas_system.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// Definición de la partícula de humo
struct SmokeParticle {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float lifetime;
    float totalLifetime;

    SmokeParticle(sf::Vector2f pos, float radius);
    void update(float deltaTime);
};


class GasSystem {
public:
    GasSystem();
    void Update(bool isSpawning);
    void Render(sf::RenderWindow& window);

    int GetParticleCount() const { return m_particles.size(); }

private:
    std::vector<SmokeParticle> m_particles;

    float m_spawnCounter;
    const float m_maxParticlesPerSec;
    const sf::Vector2f m_gasSourcePos;
};