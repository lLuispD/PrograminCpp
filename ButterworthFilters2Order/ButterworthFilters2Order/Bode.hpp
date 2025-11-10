#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <utility>

/**
 * @brief Clase Bode para graficar un diagrama de Bode (magnitud y fase)
 *        con fondo oscuro, rejilla, ejes, divisiones y textos de referencia.
 *
 * Uso típico:
 *   1. Crear un objeto Bode(posX, posY, height, width, minFreq, maxFreq).
 *   2. (Opcional) Llamar a setFont(...) para asignar la fuente de texto.
 *   3. Asignar una función de transferencia con setTransferFunction(...).
 *   4. Llamar a updateDiagram() para recalcular los datos y etiquetas.
 *   5. Dibujar en el loop SFML: window.draw(bodePlot).
 */
class Bode : public sf::Drawable {
public:
    using TransferFunction = std::function<std::pair<double, double>(double)>;

    /**
     * @param posx        Posición X donde dibujar el diagrama.
     * @param posy        Posición Y donde dibujar el diagrama.
     * @param height      Altura total (magnitud + fase).
     * @param width       Ancho total del diagrama.
     * @param minFreq     Frecuencia mínima en Hz (por defecto 1 Hz).
     * @param maxFreq     Frecuencia máxima en Hz (por defecto 10 kHz).
     */
    Bode(float posx, float posy, float height, float width,
        double minFreq = 1.0, double maxFreq = 1e4);

    /**
     * @brief Asigna la fuente de texto para las etiquetas de ejes y divisiones.
     *        Debe mantenerse viva mientras se dibuje el diagrama.
     */
    void setFont(const sf::Font& font);

    /**
     * @brief Asigna la función de transferencia que se usará para graficar.
     *        Debe retornar {magnitud_dB, fase_grados} para una frecuencia dada.
     */
    void setTransferFunction(TransferFunction tf);

    /**
     * @brief Recalcula los datos (bodeData), las curvas de magnitud y fase,
     *        la rejilla y las etiquetas de texto.
     */
    void updateDiagram();

    /**
     * @brief Configura la cantidad de subdivisiones para la rejilla
     *        - horizontalDecades: subdivisiones (verticales) por década
     *        - magDiv: divisiones horizontales para magnitud
     *        - phaseDiv: divisiones horizontales para fase
     */
    void setGridDivisions(int horizontalDecades, int magDiv, int phaseDiv);

    /**
     * @brief Cambia el rango de frecuencias (Hz).
     */
    void setFrequencyRange(double minF, double maxF);

    /**
     * @brief Ajusta el rango de dB y fase que se visualiza.
     */
    void setRangesDBPhase(double magMin, double magMax, double phaseMin, double phaseMax);

private:
    // Heredado de sf::Drawable: dibuja el contenido en el RenderTarget.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Métodos internos
    void computeBodeData(); // Calcula bodeData y rellena magnitudeCurve y phaseCurve
    void buildGrid();       // Construye rejilla, ejes y labels

private:
    float posX, posY;         // Posición en pantalla
    float width, height;      // Dimensiones totales
    double minFrequency;      // Frecuencia mínima
    double maxFrequency;      // Frecuencia máxima

    // Rango de magnitud (dB) y fase (grados) a mostrar
    double magMin, magMax;
    double phaseMin, phaseMax;

    bool transferFuncSet;     // Indica si tenemos o no una función de transferencia
    TransferFunction transferFunc;

    // Datos calculados: bodeData[i] = { freq, {mag_dB, phase_deg} }
    std::vector<std::pair<double, std::pair<double, double>>> bodeData;

    // Curvas dibujables
    sf::VertexArray magnitudeCurve;
    sf::VertexArray phaseCurve;

    // Rejilla y ejes
    sf::VertexArray gridLines; // rejilla (líneas horizontales y verticales)
    sf::VertexArray axesLines; // ejes principales (blancos)

    // Etiquetas de texto para frecuencias, dB, fase, etc.
    std::vector<sf::Text> labels;

    // Configuraciones para rejilla
    int decadesHorizontal; // nº de subdivisiones (verticales) por década
    int magDiv;            // nº de divisiones horizontales para magnitud
    int phaseDiv;          // nº de divisiones horizontales para fase

    // Fuente para dibujar texto (opcional)
    const sf::Font* fontPtr; // puntero a una fuente externa
};
