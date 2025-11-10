// application.cpp
#include "Application.hpp"

Application* Application::Instance = nullptr;
float		 Application::DT = 0.0f;
const float& dt = Application::DT;

Application::Application()
    : m_isGasSpawning(false)
{
    Instance = this;
    InitWindow();

    // Crear los componentes del sistema
    m_sensor = new Sensor();
    m_gasSystem = new GasSystem();
    m_gui = new Gui();
}

Application::~Application() {
    delete m_sensor;
    delete m_gasSystem;
    delete m_gui;
}

void Application::Run() {
    m_dtClock.restart();

    while (m_window.isOpen()) {
        DT = m_dtClock.restart().asSeconds();

        HandleEvents();
        Update();

        m_window.clear(sf::Color(30, 30, 30));
        Render();
        m_window.display();
    }
}

void Application::Update() {
    // 1. Actualizar el sistema de gas
    m_gasSystem->Update(m_isGasSpawning);

    // 2. Obtener el resultado del gas y actualizar el sensor
    int particleCount = m_gasSystem->GetParticleCount();
    m_sensor->Update(particleCount);

    // 3. Actualizar la GUI con los nuevos datos del sensor
    m_gui->Update(*m_sensor);
}

void Application::Render() {
    // Dibujar el humo primero (detrás)
    m_gasSystem->Render(m_window);

    // Dibujar la GUI encima
    m_gui->Render(m_window);
}

void Application::HandleEvents() {
    // Comprobar eventos (un solo fotograma)
    while (m_window.pollEvent(m_event)) {
        if (m_event.type == sf::Event::Closed)
            m_window.close();

        // Control del umbral con la rueda del ratón
        if (m_event.type == sf::Event::MouseWheelScrolled) {
            if (m_event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                m_sensor->AdjustThreshold(m_event.mouseWheelScroll.delta);
            }
        }
    }

    // Comprobar estado (sostenido)
    m_isGasSpawning = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Application::InitWindow() {
    sf::VideoMode mode;
    mode.width = WINDOW_WIDTH;
    mode.height = WINDOW_HEIGHT;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    m_window.create(mode, "Simulador de Sensor MQ-2 Basado en datasheet", sf::Style::Close, settings);
    m_window.setFramerateLimit(144);
}