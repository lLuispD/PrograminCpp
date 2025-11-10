#include "Bode.hpp"
#include <cmath>
#include <sstream>
#include <iomanip>

static const double LOG10 = std::log(10.0);

Bode::Bode(float posx, float posy, float height, float width,
    double minFreq, double maxFreq)
    : posX(posx), posY(posy), width(width), height(height),
    minFrequency(minFreq), maxFrequency(maxFreq),
    magMin(-60.0), magMax(10.0),
    phaseMin(-180.0), phaseMax(180.0),
    transferFuncSet(false),
    magnitudeCurve(sf::LineStrip),
    phaseCurve(sf::LineStrip),
    gridLines(sf::Lines),
    axesLines(sf::Lines),
    decadesHorizontal(9), magDiv(8), phaseDiv(6),
    fontPtr(nullptr)
{
}

void Bode::setFont(const sf::Font& font) {
    fontPtr = &font;
}

void Bode::setTransferFunction(TransferFunction tf) {
    transferFunc = tf;
    transferFuncSet = true;
}

void Bode::updateDiagram() {
    computeBodeData();
    buildGrid();
}

void Bode::setGridDivisions(int horizontalDecades, int magDivisions, int phaseDivisions) {
    decadesHorizontal = horizontalDecades;
    magDiv = magDivisions;
    phaseDiv = phaseDivisions;
}

void Bode::setFrequencyRange(double minF, double maxF) {
    minFrequency = minF;
    maxFrequency = maxF;
}

void Bode::setRangesDBPhase(double mMin, double mMax, double pMin, double pMax) {
    magMin = mMin;
    magMax = mMax;
    phaseMin = pMin;
    phaseMax = pMax;
}

// ---------------------------------------------------
// 1) Generar datos de Bode (magnitud y fase) en bodeData
// 2) Crear VertexArrays de la curva
// ---------------------------------------------------
void Bode::computeBodeData() {
    bodeData.clear();
    magnitudeCurve.clear();
    phaseCurve.clear();

    const int numPoints = 200;

    double logFmin = std::log10(minFrequency);
    double logFmax = std::log10(maxFrequency);
    double step = (logFmax - logFmin) / (numPoints - 1);

    for (int i = 0; i < numPoints; i++) {
        double logf = logFmin + i * step;
        double freq = std::pow(10.0, logf);

        double magdB = 0.0;
        double phasedeg = 0.0;
        if (transferFuncSet) {
            auto res = transferFunc(freq);
            magdB = res.first;     // magnitud en dB
            phasedeg = res.second; // fase en grados
        }
        bodeData.push_back({ freq, {magdB, phasedeg} });
    }

    magnitudeCurve.setPrimitiveType(sf::LineStrip);
    phaseCurve.setPrimitiveType(sf::LineStrip);

    auto mapX = [&](double f) {
        double lf = std::log10(f);
        double ratio = (lf - logFmin) / (logFmax - logFmin);
        return posX + static_cast<float>(ratio * width);
        };

    auto mapMag = [&](double magdB) {
        double ratio = (magdB - magMin) / (magMax - magMin);
        return posY + (1.0f - static_cast<float>(ratio)) * (height / 2.0f);
        };

    auto mapPhase = [&](double phdeg) {
        double ratio = (phdeg - phaseMin) / (phaseMax - phaseMin);
        return (posY + height / 2.0f) + (1.0f - static_cast<float>(ratio)) * (height / 2.0f);
        };

    for (auto& point : bodeData) {
        double f = point.first;
        double magdB = point.second.first;
        double phdeg = point.second.second;

        sf::Vector2f vMag(mapX(f), mapMag(magdB));
        magnitudeCurve.append(sf::Vertex(vMag, sf::Color::Cyan));

        sf::Vector2f vPh(mapX(f), mapPhase(phdeg));
        phaseCurve.append(sf::Vertex(vPh, sf::Color::Yellow));
    }
}

// ---------------------------------------------------
// Construir la rejilla (grid), ejes y labels de texto
// ---------------------------------------------------
void Bode::buildGrid() {
    gridLines.clear();
    axesLines.clear();
    labels.clear();

    gridLines.setPrimitiveType(sf::Lines);
    axesLines.setPrimitiveType(sf::Lines);

    // Fondo: se dibuja en draw() con un rect negro

    // Ejes principales en blanco
    //  - Vertical magnitud: posX, posY -> posY+height/2
    //  - Vertical fase: posX, posY+height/2 -> posY+height
    //  - Horizontal magnitud: posY+height/2
    //  - Horizontal fase: posY+height
    {
        // Eje vertical magnitud
        sf::Vertex v1(sf::Vector2f(posX, posY), sf::Color::White);
        sf::Vertex v2(sf::Vector2f(posX, posY + height / 2.0f), sf::Color::White);
        axesLines.append(v1); axesLines.append(v2);

        // Eje vertical fase
        sf::Vertex v3(sf::Vector2f(posX, posY + height / 2.0f), sf::Color::White);
        sf::Vertex v4(sf::Vector2f(posX, posY + height), sf::Color::White);
        axesLines.append(v3); axesLines.append(v4);

        // Eje horizontal dB (arriba)
        sf::Vertex v5(sf::Vector2f(posX, posY + height / 2.0f), sf::Color::White);
        sf::Vertex v6(sf::Vector2f(posX + width, posY + height / 2.0f), sf::Color::White);
        axesLines.append(v5); axesLines.append(v6);

        // Eje horizontal fase (abajo)
        sf::Vertex v7(sf::Vector2f(posX, posY + height), sf::Color::White);
        sf::Vertex v8(sf::Vector2f(posX + width, posY + height), sf::Color::White);
        axesLines.append(v7); axesLines.append(v8);
    }

    // Para dibujar etiquetas de texto
    auto makeLabel = [&](const std::string& str, float x, float y, sf::Color color) {
        if (!fontPtr) return; // sin fuente, no dibujamos
        sf::Text txt;
        txt.setFont(*fontPtr);
        txt.setString(str);
        txt.setCharacterSize(12);
        txt.setFillColor(color);
        txt.setPosition(x, y);
        labels.push_back(txt);
        };

    // Función de mapeo log freq -> x
    double logFmin = std::log10(minFrequency);
    double logFmax = std::log10(maxFrequency);
    auto freqToX = [&](double freq) {
        double lf = std::log10(freq);
        double ratio = (lf - logFmin) / (logFmax - logFmin);
        return posX + static_cast<float>(ratio * width);
        };

    // --- Rejilla vertical por décadas y subdivisiones ---
    int minDecade = static_cast<int>(std::floor(logFmin));
    int maxDecade = static_cast<int>(std::ceil(logFmax));

    for (int d = minDecade; d <= maxDecade; d++) {
        for (int i = 1; i <= decadesHorizontal; i++) {
            double freq = i * std::pow(10.0, d);
            if (freq < minFrequency || freq > maxFrequency) continue;

            float xLine = freqToX(freq);
            // línea vertical
            sf::Vertex top(sf::Vector2f(xLine, posY), sf::Color(80, 80, 80));
            sf::Vertex bottom(sf::Vector2f(xLine, posY + height), sf::Color(80, 80, 80));
            gridLines.append(top);
            gridLines.append(bottom);

            // Etiqueta de frecuencia (solo si i=1,2,5,10 etc. o como prefieras)
            // Para simplificar, etiquetamos i=1.
            if (i == 1) {
                // freq = 1 * 10^d
                // Ej: 10^2=100, 10^3=1000, etc.
                std::ostringstream oss;
                if (d >= 3)
                    oss << (int)std::pow(10.0, d - 3) << "k"; // e.g. 1k, 10k...
                else if (d >= 0)
                    oss << (int)std::pow(10.0, d);
                else
                    oss << std::fixed << std::setprecision(0) << std::pow(10.0, d);

                float labelX = xLine + 2.f;
                float labelY = posY + height - 15.f;
                makeLabel(oss.str(), labelX, labelY, sf::Color::White);
            }
        }
    }

    // --- Rejilla horizontal para magnitud ---
    auto dBToY = [&](double dB) {
        double ratio = (dB - magMin) / (magMax - magMin);
        return posY + (1.0f - static_cast<float>(ratio)) * (height / 2.0f);
        };
    double dBstep = (magMax - magMin) / magDiv;
    for (int m = 0; m <= magDiv; m++) {
        double valdB = magMin + m * dBstep;
        float yLine = dBToY(valdB);

        sf::Vertex left(sf::Vector2f(posX, yLine), sf::Color(80, 80, 80));
        sf::Vertex right(sf::Vector2f(posX + width, yLine), sf::Color(80, 80, 80));
        gridLines.append(left);
        gridLines.append(right);

        // Etiqueta dB (en el borde izquierdo)
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(0) << valdB << " dB";
        makeLabel(oss.str(), posX + 5.f, yLine - 10.f, sf::Color::White);
    }

    // --- Rejilla horizontal para fase ---
    auto phaseToY = [&](double phase) {
        double ratio = (phase - phaseMin) / (phaseMax - phaseMin);
        return (posY + height / 2.0f) + (1.0f - static_cast<float>(ratio)) * (height / 2.0f);
        };
    double phaseStep = (phaseMax - phaseMin) / phaseDiv;
    for (int p = 0; p <= phaseDiv; p++) {
        double ph = phaseMin + p * phaseStep;
        float yLine = phaseToY(ph);

        sf::Vertex left(sf::Vector2f(posX, yLine), sf::Color(80, 80, 80));
        sf::Vertex right(sf::Vector2f(posX + width, yLine), sf::Color(80, 80, 80));
        gridLines.append(left);
        gridLines.append(right);

        // Etiqueta de fase
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(0) << ph << "°";
        makeLabel(oss.str(), posX + 5.f, yLine - 10.f, sf::Color::White);
    }

    // Etiqueta general ejes (opcional): "Frequency (Hz)" abajo, "Magnitude (dB)" arriba, etc.
    if (fontPtr) {
        sf::Text freqLabel("Frequency (Hz)", *fontPtr, 14);
        freqLabel.setFillColor(sf::Color::White);
        freqLabel.setPosition(posX + width / 2.f - 50.f, posY + height - 20.f);
        labels.push_back(freqLabel);

        sf::Text magLabel("Magnitude (dB)", *fontPtr, 14);
        magLabel.setFillColor(sf::Color::White);
        magLabel.setPosition(posX + 10.f, posY + 5.f);
        labels.push_back(magLabel);

        sf::Text phaseLabel("Phase (deg)", *fontPtr, 14);
        phaseLabel.setFillColor(sf::Color::White);
        phaseLabel.setPosition(posX + 10.f, posY + height / 2.f + 5.f);
        labels.push_back(phaseLabel);
    }
}

// ---------------------------------------------------
// Dibuja el fondo, la rejilla, los ejes, las curvas y los labels
// ---------------------------------------------------
void Bode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Fondo negro
    sf::RectangleShape bg(sf::Vector2f(width, height));
    bg.setPosition(posX, posY);
    bg.setFillColor(sf::Color::Black);
    target.draw(bg, states);

    // Rejilla
    target.draw(gridLines, states);

    // Ejes
    target.draw(axesLines, states);

    // Curvas
    if (transferFuncSet) {
        target.draw(magnitudeCurve, states);
        target.draw(phaseCurve, states);
    }

    // Etiquetas de texto
    for (const auto& label : labels) {
        target.draw(label, states);
    }
}
