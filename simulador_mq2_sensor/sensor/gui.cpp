// gui.cpp
#include "gui.hpp"
#include "application.hpp" // Para WINDOW_WIDTH/HEIGHT
#include <iostream>
#include <sstream>
#include <iomanip>

// Función de mapeo (privada a este archivo)
namespace {
    float map(float value, float start1, float stop1, float start2, float stop2) {
        return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
    }
}

Gui::Gui() {
    // Cargar recursos
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Error: No se pudo cargar la fuente 'arial.ttf'.\n";
    }
    if (!m_sensorTexture.loadFromFile("mq2_sensor.png")) {
        std::cerr << "Error: No se pudo cargar la imagen 'mq2_sensor.png'.\n";
    }

    // Inicializar todos los elementos gráficos
    InitGraphics();
}

void Gui::InitGraphics() {
    sf::Vector2f sensorPos(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
    const float TARGET_SENSOR_DIAMETER = 80.0f;

    // Sprite del sensor
    m_sensorSprite.setTexture(m_sensorTexture);
    sf::Vector2u texSize = m_sensorTexture.getSize();
    float maxTexDim = std::max(texSize.x, texSize.y);
    float scaleFactor = TARGET_SENSOR_DIAMETER / maxTexDim;
    m_sensorSprite.setScale(scaleFactor, scaleFactor);
    m_sensorSprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
    m_sensorSprite.setPosition(sensorPos);

    // Texto: Concentración
    m_concentrationTitle.setFont(m_font);
    m_concentrationTitle.setString("Concentracion (PPM)");
    m_concentrationTitle.setCharacterSize(18);
    m_concentrationTitle.setFillColor(sf::Color::Cyan);
    m_concentrationTitle.setOrigin(m_concentrationTitle.getLocalBounds().width / 2.f, 0);
    m_concentrationTitle.setPosition(sensorPos.x, 50.f);

    m_concentrationValueText.setFont(m_font);
    m_concentrationValueText.setString("10 PPM");
    m_concentrationValueText.setCharacterSize(40);
    m_concentrationValueText.setFillColor(sf::Color::Cyan);
    m_concentrationValueText.setPosition(sensorPos.x, 80.f); // Se centrará en Update

    // GUI: Salida Analógica
    m_analogTitle.setFont(m_font);
    m_analogTitle.setString("Salida Analogica");
    m_analogTitle.setCharacterSize(18);
    m_analogTitle.setPosition(50.f, 150.f);

    m_analogBarBg.setSize(sf::Vector2f(50.f, 300.f));
    m_analogBarBg.setPosition(75.f, 190.f);
    m_analogBarBg.setFillColor(sf::Color(50, 50, 50));
    m_analogBarBg.setOutlineColor(sf::Color::White);
    m_analogBarBg.setOutlineThickness(2.f);

    m_analogBar.setSize(sf::Vector2f(50.f, 0.f));
    m_analogBar.setPosition(75.f, 490.f);
    m_analogBar.setFillColor(sf::Color::Yellow);

    m_analogVoltageText.setFont(m_font);
    m_analogVoltageText.setString("0 mV");
    m_analogVoltageText.setCharacterSize(30);
    m_analogVoltageText.setPosition(140.f, 250.f);

    // GUI: Umbral
    m_thresholdLine.setSize(sf::Vector2f(60.f, 2.f));
    m_thresholdLine.setFillColor(sf::Color::Red);

    m_thresholdText.setFont(m_font);
    m_thresholdText.setString("Umbral: 0 mV");
    m_thresholdText.setCharacterSize(16);
    m_thresholdText.setPosition(50.f, 500.f);
    m_thresholdText.setFillColor(sf::Color::Red);
     

    m_digitalLed.setRadius(30.f);
    m_digitalLed.setOrigin(30.f, 30.f);
    m_digitalLed.setPosition(675.f, 300.f);
    m_digitalLed.setOutlineColor(sf::Color(200, 200, 200));
    m_digitalLed.setOutlineThickness(2.f);

    m_digitalLedGlow.setRadius(40.f);
    m_digitalLedGlow.setOrigin(40.f, 40.f);
    m_digitalLedGlow.setPosition(675.f, 300.f);
    m_digitalLedGlow.setFillColor(sf::Color::Transparent);
     
    // GUI: Instrucciones
    m_instructions.setFont(m_font);
    m_instructions.setString("Clic izquierdo para liberar gas.\nRueda central para ajustar el umbral (mV).");
    m_instructions.setCharacterSize(16);
    m_instructions.setPosition(10.f, 560.f);
    m_instructions.setFillColor(sf::Color(200, 200, 200));
}

void Gui::Update(const Sensor& sensor) {
    // Obtener todos los valores del sensor
    float analogVoltage = sensor.GetAnalogVoltage();
    float ppm = sensor.GetPPM();
    float threshold = sensor.GetThresholdVoltage();
    bool digitalOn = sensor.GetDigitalValue();

    // Formatear texto
    std::ostringstream ppmStream, voltageStream, thresholdStream;

    ppmStream << std::fixed << std::setprecision(0) << ppm << " PPM";
    m_concentrationValueText.setString(ppmStream.str());
    m_concentrationValueText.setOrigin(m_concentrationValueText.getLocalBounds().width / 2.f, 0);

    voltageStream << std::fixed << std::setprecision(0) << analogVoltage << " mV";
    m_analogVoltageText.setString(voltageStream.str());

    thresholdStream << "Umbral: " << std::fixed << std::setprecision(0) << threshold << " mV";
    m_thresholdText.setString(thresholdStream.str());

    // Actualizar barra y línea de umbral
    float barHeight = map(analogVoltage, sensor.GetMinVoltage(), sensor.GetMaxVoltage(), 0, 300);
    m_analogBar.setSize(sf::Vector2f(50.f, -barHeight));

    float thresholdY = map(threshold, sensor.GetMinVoltage(), sensor.GetMaxVoltage(), 490.f, 190.f);
    m_thresholdLine.setPosition(70.f, thresholdY);

    // Actualizar LED digital
    if (digitalOn) {
        m_digitalLed.setFillColor(sf::Color::Red);
        m_digitalLedGlow.setFillColor(sf::Color(255, 0, 0, 80));
        m_digitalStateText.setString("ON");
        m_digitalStateText.setFillColor(sf::Color::Red);
    }
    else {
        m_digitalLed.setFillColor(sf::Color(50, 0, 0));
        m_digitalLedGlow.setFillColor(sf::Color::Transparent);
        m_digitalStateText.setString("OFF");
        m_digitalStateText.setFillColor(sf::Color::White);
    }
    m_digitalStateText.setOrigin(m_digitalStateText.getLocalBounds().width / 2.f, 0);
}

void Gui::Render(sf::RenderWindow& window) {
    // Dibujar todos los elementos
    window.draw(m_sensorSprite);

    window.draw(m_concentrationTitle);
    window.draw(m_concentrationValueText);

    window.draw(m_analogTitle);
    window.draw(m_analogBarBg);
    window.draw(m_analogBar);
    window.draw(m_analogVoltageText);
    window.draw(m_thresholdLine);
    window.draw(m_thresholdText);

    window.draw(m_digitalTitle);
    window.draw(m_digitalLedGlow);
    window.draw(m_digitalLed);
    window.draw(m_digitalStateText);

    window.draw(m_instructions);
}