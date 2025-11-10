// gui.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include "sensor.hpp" // Necesita leer datos del sensor

class Gui {
public:
    Gui();
    void Update(const Sensor& sensor);
    void Render(sf::RenderWindow& window);

private:
    void InitGraphics();

    // Recursos
    sf::Font m_font;
    sf::Texture m_sensorTexture;

    // Elementos gráficos
    sf::Sprite m_sensorSprite;

    sf::Text m_concentrationTitle;
    sf::Text m_concentrationValueText;

    sf::Text m_analogTitle;
    sf::RectangleShape m_analogBarBg;
    sf::RectangleShape m_analogBar;
    sf::Text m_analogVoltageText;

    sf::RectangleShape m_thresholdLine;
    sf::Text m_thresholdText;

    sf::Text m_digitalTitle;
    sf::CircleShape m_digitalLed;
    sf::CircleShape m_digitalLedGlow;
    sf::Text m_digitalStateText;

    sf::Text m_instructions;
};