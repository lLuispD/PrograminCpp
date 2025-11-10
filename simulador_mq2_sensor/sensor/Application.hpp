// application.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include "sensor.hpp"
#include "gas_system.hpp"
#include "gui.hpp"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

class Application {
public:
    Application();
    ~Application();
    void Run();

    // Singleton (opcional, pero común)
    static Application* Instance;
    // Delta time global
    static float DT;

private:
    void InitWindow();
    void HandleEvents();
    void Update();
    void Render();

    sf::RenderWindow m_window;
    sf::Event m_event;
    sf::Clock m_dtClock;

    // Componentes del sistema
    Sensor* m_sensor;
    GasSystem* m_gasSystem;
    Gui* m_gui;

    // Estado de la aplicación
    bool m_isGasSpawning;
};

// Referencia global a DT
extern const float& dt;