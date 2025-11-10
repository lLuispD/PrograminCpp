#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>

// Función auxiliar de mapeo (sin cambios)
float map(float value, float start1, float stop1, float start2, float stop2) {
    return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

// Estructura para una partícula de humo (sin cambios)
struct SmokeParticle {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float lifetime;
    float totalLifetime;

    SmokeParticle(sf::Vector2f pos, float radius) {
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
    void update(float deltaTime) {
        lifetime -= deltaTime;
        shape.move(velocity * deltaTime);
        float lifePercent = std::max(0.f, lifetime / totalLifetime);
        sf::Uint8 newAlpha = static_cast<sf::Uint8>(std::pow(lifePercent, 2) * 60);
        shape.setFillColor(sf::Color(200, 200, 200, newAlpha));
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    // --- Configuración de la Ventana ---
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simulador de Sensor MQ-2 v6.2 (Datasheet Logic)");
    window.setFramerateLimit(60);

    // --- Reloj para Delta Time ---
    sf::Clock deltaClock;

    // --- Cargar Recursos ---
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { /* ... error ... */ return -1; }
    sf::Texture sensorTexture;
    if (!sensorTexture.loadFromFile("mq2_sensor.png")) { /* ... error ... */ return -1; }

    // --- Constantes Visuales ---
    sf::Vector2f sensorPos(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
    const float TARGET_SENSOR_DIAMETER = 80.0f;

    // --- Sprite y Auto-Escalado (sin cambios) ---
    sf::Sprite sensorSprite(sensorTexture);
    sf::Vector2u texSize = sensorTexture.getSize();
    float maxTexDim = std::max(texSize.x, texSize.y);
    float scaleFactor = TARGET_SENSOR_DIAMETER / maxTexDim;
    sensorSprite.setScale(scaleFactor, scaleFactor);
    sensorSprite.setOrigin(texSize.x / 2.f, texSize.y / 2.f);
    sensorSprite.setPosition(sensorPos);

    // *** NUEVAS CONSTANTES DE SIMULACIÓN (BASADAS EN DATASHEET) ***
    const float VC = 5000.0f; // Vc = 5V (5000mV) 
    const float RL = 20000.0f; // RL = 20kOhms 
    const float RO = 6800.0f;  // Ro base calculado (ver notas) [cite: 13, 104, 109]
    // Rs en aire limpio (Rs/Ro = 10) 
    const float RS_CLEAN_AIR = 10.0f * RO; // 68000 Ohms
    // Rs en 1000ppm humo (Rs/Ro = 2.0) 
    const float RS_1000PPM_SMOKE = 2.0f * RO; // 13600 Ohms

    // Calcular el rango de voltaje de salida REAL
    const float minVoltage = VC * (RL / (RS_CLEAN_AIR + RL));     // ~1136 mV
    const float maxVoltage = VC * (RL / (RS_1000PPM_SMOKE + RL)); // ~2976 mV

    const float minPPM = 10.0f;  // Solo para visualización
    const float maxPPM = 1000.0f; // Solo para visualización
    const int MAX_EFFECTIVE_PARTICLES = 300;

    // --- Variables de Estado ---
    float analogVoltage = minVoltage; // Iniciar en el voltaje de aire limpio
    float gasConcentrationPPM = minPPM;
    bool digitalValue = false;
    float digitalThresholdVoltage = (minVoltage + maxVoltage) / 2.0f; // Poner el umbral en el medio

    // --- Sistema de Partículas (sin cambios) ---
    std::vector<SmokeParticle> particles;
    float spawnCounter = 0.0f;
    const float MAX_PARTICLES_PER_SEC = 200.0f;

    // --- Elementos Gráficos (Visuales) ---
    sf::Vector2f gasSourcePos(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 50.f);

    // Círculo de fondo transparente (sin cambios)
    sf::CircleShape sensorBody(40.f);
    sensorBody.setOrigin(40.f, 40.f);
    sensorBody.setPosition(sensorPos);
    sensorBody.setFillColor(sf::Color::Transparent);
    sensorBody.setOutlineThickness(0.f);

    // ... (Todos los demás elementos de la GUI no cambian) ...
    sf::Text concentrationTitle("Concentracion (PPM)", font, 18);
    concentrationTitle.setFillColor(sf::Color::Cyan);
    concentrationTitle.setOrigin(concentrationTitle.getLocalBounds().width / 2.f, 0);
    concentrationTitle.setPosition(sensorPos.x, 50.f);
    sf::Text concentrationValueText("10 PPM", font, 40);
    concentrationValueText.setFillColor(sf::Color::Cyan);
    concentrationValueText.setOrigin(concentrationValueText.getLocalBounds().width / 2.f, 0);
    concentrationValueText.setPosition(sensorPos.x, 80.f);
    sf::Text analogTitle("Salida Analogica", font, 18);
    analogTitle.setPosition(50.f, 150.f);
    sf::RectangleShape analogBarBg(sf::Vector2f(50.f, 300.f));
    analogBarBg.setPosition(75.f, 190.f);
    analogBarBg.setFillColor(sf::Color(50, 50, 50));
    analogBarBg.setOutlineColor(sf::Color::White);
    analogBarBg.setOutlineThickness(2.f);
    sf::RectangleShape analogBar(sf::Vector2f(50.f, 0.f));
    analogBar.setPosition(75.f, 490.f);
    analogBar.setFillColor(sf::Color::Yellow);
    sf::Text analogVoltageText("200 mV", font, 30);
    analogVoltageText.setPosition(140.f, 250.f);
    sf::RectangleShape thresholdLine(sf::Vector2f(60.f, 2.f));
    thresholdLine.setFillColor(sf::Color::Red);
    sf::Text thresholdText("Umbral: 2500 mV", font, 16);
    thresholdText.setPosition(50.f, 500.f);
    thresholdText.setFillColor(sf::Color::Red);
    sf::Text digitalTitle("Salida Digital", font, 18);
    digitalTitle.setPosition(600.f, 150.f);
    sf::CircleShape digitalLed(30.f);
    digitalLed.setOrigin(30.f, 30.f);
    digitalLed.setPosition(675.f, 300.f);
    digitalLed.setOutlineColor(sf::Color(200, 200, 200));
    digitalLed.setOutlineThickness(2.f);
    sf::CircleShape digitalLedGlow(40.f);
    digitalLedGlow.setOrigin(40.f, 40.f);
    digitalLedGlow.setPosition(675.f, 300.f);
    digitalLedGlow.setFillColor(sf::Color::Transparent);
    sf::Text digitalStateText("OFF", font, 40);
    digitalStateText.setOrigin(digitalStateText.getLocalBounds().width / 2.f, 0);
    digitalStateText.setPosition(675.f, 350.f);
    sf::Text instructions("Manten presionado el CLIC IZQUIERDO para liberar gas.\nUsa la RUEDA DEL RATON para ajustar el umbral (mV).", font, 16);
    instructions.setPosition(10.f, 560.f);
    instructions.setFillColor(sf::Color(200, 200, 200));

    // --- Bucle Principal de la Simulación ---
    while (window.isOpen()) {
        sf::Time dt = deltaClock.restart();
        float deltaTime = dt.asSeconds();

        // --- Manejo de Eventos ---
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    digitalThresholdVoltage += event.mouseWheelScroll.delta * 50.0f;
                    // *** CAMBIO: El clamp usa los voltajes calculados ***
                    digitalThresholdVoltage = std::max(minVoltage, std::min(maxVoltage, digitalThresholdVoltage));
                }
            }
        }

        // --- Lógica de Actualización (Update) ---

        // 1. Generación de partículas (sin cambios)
        float spawnRateThisFrame = 0.0f;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            spawnRateThisFrame = MAX_PARTICLES_PER_SEC;
        }
        spawnCounter += spawnRateThisFrame * deltaTime;
        while (spawnCounter >= 1.0f) {
            float radius = map(rand() % 100, 0, 99, 13.f, 23.f);
            particles.push_back(SmokeParticle(gasSourcePos, radius));
            spawnCounter -= 1.0f;
        }

        // 2. Actualizar y eliminar partículas muertas (sin cambios)
        for (int i = particles.size() - 1; i >= 0; --i) {
            particles[i].update(deltaTime);
            if (particles[i].lifetime <= 0) {
                particles.erase(particles.begin() + i);
            }
        }

        // *** 3. MEDICIÓN DEL SENSOR (LÓGICA DEL DATASHEET) ***
        float particleCount = static_cast<float>(particles.size());
        float normalizedConcentration = std::min(1.0f, particleCount / MAX_EFFECTIVE_PARTICLES);
        // Usamos la curva de potencia para simular la respuesta log-log no lineal del sensor
        float sensorResponse = std::pow(normalizedConcentration, 0.7f);

        // Mapear PPM para visualización (sin cambios)
        gasConcentrationPPM = map(normalizedConcentration, 0.0f, 1.0f, minPPM, maxPPM);

        // 3a. Calcular la resistencia actual (Rs)
        // Mapeamos la respuesta no lineal al rango de resistencia (de aire limpio a humo)
        float currentRs = map(sensorResponse, 0.0f, 1.0f, RS_CLEAN_AIR, RS_1000PPM_SMOKE);

        // 3b. Calcular Vout usando la fórmula del divisor de voltaje 
        analogVoltage = VC * (RL / (currentRs + RL));

        // 3c. Calcular el estado digital (sin cambios)
        digitalValue = (analogVoltage > digitalThresholdVoltage);


        // --- Actualizar Visuales (GUI) ---
        // *** CAMBIO: El mapeo de la barra y el umbral usan los voltajes calculados ***
        float barHeight = map(analogVoltage, minVoltage, maxVoltage, 0, 300);
        analogBar.setSize(sf::Vector2f(50.f, -barHeight));

        float thresholdY = map(digitalThresholdVoltage, minVoltage, maxVoltage, 490.f, 190.f);
        thresholdLine.setPosition(70.f, thresholdY);

        // ... (resto de la actualización de texto sin cambios) ...
        std::ostringstream ppmStream, voltageStream, thresholdStream;
        ppmStream << std::fixed << std::setprecision(0) << gasConcentrationPPM << " PPM";
        concentrationValueText.setString(ppmStream.str());
        concentrationValueText.setOrigin(concentrationValueText.getLocalBounds().width / 2.f, 0);
        voltageStream << std::fixed << std::setprecision(0) << analogVoltage << " mV";
        analogVoltageText.setString(voltageStream.str());
        thresholdStream << "Umbral: " << std::fixed << std::setprecision(0) << digitalThresholdVoltage << " mV";
        thresholdText.setString(thresholdStream.str());
        if (digitalValue) {
            digitalLed.setFillColor(sf::Color::Red);
            digitalLedGlow.setFillColor(sf::Color(255, 0, 0, 80));
            digitalStateText.setString("ON");
            digitalStateText.setFillColor(sf::Color::Red);
        }
        else {
            digitalLed.setFillColor(sf::Color(50, 0, 0));
            digitalLedGlow.setFillColor(sf::Color::Transparent);
            digitalStateText.setString("OFF");
            digitalStateText.setFillColor(sf::Color::White);
        }
        digitalStateText.setOrigin(digitalStateText.getLocalBounds().width / 2.f, 0);

        // --- Dibujo (Render) ---
        window.clear(sf::Color(30, 30, 30));
        for (const auto& p : particles) { window.draw(p.shape, sf::BlendAdd); }
        window.draw(sensorSprite);
        window.draw(concentrationTitle);
        window.draw(concentrationValueText);
        window.draw(analogTitle);
        window.draw(analogBarBg);
        window.draw(analogBar);
        window.draw(analogVoltageText);
        window.draw(thresholdLine);
        window.draw(thresholdText);
        window.draw(digitalTitle);
        window.draw(digitalLedGlow);
        window.draw(digitalLed);
        window.draw(digitalStateText);
        window.draw(instructions);
        window.display();
    }

    return 0;
}