#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class Particle {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Particle(float x, float y, float radius) {
        shape.setPosition(x, y);
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Green);
        velocity = sf::Vector2f(0.f, 0.f);
    }

    void update(float deltaTime, const std::vector<Particle>& particles) {
        // Atraer a otras partículas
        for (const auto& p : particles) {
            if (&p != this) {
                sf::Vector2f dir = p.shape.getPosition() - shape.getPosition();
                float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);
                if (distance > 0 && distance < 100.f) {
                    float force = (shape.getRadius() * p.shape.getRadius()) / (distance * distance);  // Ley de la gravedad proporcional al tamaño
                    dir = dir / distance * force; // Normalizamos el vector y aplicamos la fuerza
                    velocity += dir;
                }
            }
        }

        // Actualizamos la posición de la partícula
        shape.move(velocity * deltaTime);

        // Verificamos si salió de la pantalla
        if (shape.getPosition().x < 0 || shape.getPosition().x > WINDOW_WIDTH || shape.getPosition().y < 0 || shape.getPosition().y > WINDOW_HEIGHT) {
            shape.setRadius(0);  // "Destruir" la partícula
        }
    }
};

int main() {
    // Crear la ventana
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simulación de Partículas");
    std::vector<Particle> particles;
    bool fastForward = false;
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Manejo de eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                // Crear una nueva partícula en el punto de clic
                if (event.mouseButton.button == sf::Mouse::Left) {
                    float radius = 10.f; // Tamaño inicial de la partícula
                    particles.push_back(Particle(event.mouseButton.x, event.mouseButton.y, radius));
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift) {
                    fastForward = true;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift) {
                    fastForward = false;
                }
            }
        }

        // Actualización de las partículas
        for (auto& particle : particles) {
            particle.update(fastForward ? deltaTime * 2 : deltaTime, particles);
        }

        // Eliminar partículas "destruidas"
        particles.erase(std::remove_if(particles.begin(), particles.end(), [](const Particle& p) {
            return p.shape.getRadius() == 0;
            }), particles.end());

        // Limpiar la pantalla
        window.clear();

        // Dibujar las partículas
        for (const auto& particle : particles) {
            window.draw(particle.shape);
        }

        // Mostrar la ventana
        window.display();
    }

    return 0;
}
