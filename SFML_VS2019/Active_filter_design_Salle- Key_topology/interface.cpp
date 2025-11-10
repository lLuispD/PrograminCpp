#include "interface.hpp"
#include <sstream>
#include <iomanip>

#define fontAddress "../Fonts/arial.ttf"


/******************************************************************* TEXTO *******************************************************************/
// Constructor por defecto
UI::Text::Text() {
    if (!fuente.loadFromFile(fontAddress)) {
        std::cerr << "No se pudo cargar la fuente! " << fontAddress << std::endl;
    }
    this->texto.setFont(fuente);
}

// Constructor con parámetros
UI::Text::Text(const std::string& txt, float x, float y, unsigned int tamanio, sf::Color color, float RotationAngle) {
    if (!fuente.loadFromFile(fontAddress)) {
        std::cerr << "No se pudo cargar la fuente! " << fontAddress << std::endl;
    }
    this->texto.setString(txt);
    this->texto.setFont(fuente);
    this->texto.setCharacterSize(tamanio);
    this->texto.setFillColor(color);
    this->texto.setPosition(x, y);
    this->texto.setRotation(-1 * RotationAngle);
}

void UI::Text::setText(const std::string& newTxt) {
    texto.setString(newTxt);
}

void UI::Text::setPosicion(float x, float y) {
    texto.setPosition(x, y);
}

void UI::Text::setZise(unsigned int newSize) {
    texto.setCharacterSize(newSize);
}

void UI::Text::setColor(sf::Color color) {
    texto.setFillColor(color);
}

void UI::Text::rotateTo(float Angle) {
    texto.setRotation(-1*Angle);
}


void UI::Text::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(texto, states);
}

/******************************************************************* DROPDOWN *******************************************************************/

UI::Dropdown::Dropdown(std::vector<std::string> optionsList, float posx, float posy, float height, float width)
	: optionsList(optionsList), posx(posx), posy(posy), height(height), width(width), selectedOption(optionsList[0]) {

	font.loadFromFile(fontAddress);

	dropdownBox.setSize(sf::Vector2f(width, height));
	dropdownBox.setPosition(posx, posy);
	dropdownBox.setFillColor(sf::Color::White);
	dropdownBox.setOutlineColor(sf::Color::Black);
	dropdownBox.setOutlineThickness(2);

	textBox.setFont(font);
	textBox.setString(selectedOption);  // Usa la opción inicial
	textBox.setCharacterSize(18);
	textBox.setFillColor(sf::Color::Black);
	textBox.setPosition(posx + 10, posy + 5);

	for (size_t i = 0; i < optionsList.size(); i++) {
		sf::RectangleShape optionBox(sf::Vector2f(width, height));
		optionBox.setPosition(posx, posy + (i + 1) * height);
		optionBox.setFillColor(sf::Color::White);
		optionBox.setOutlineColor(sf::Color::Black);
		optionBox.setOutlineThickness(1);
		optionsBoxes.push_back(optionBox);

		sf::Text optionText;
		optionText.setFont(font);
		optionText.setString(optionsList[i]);
		optionText.setCharacterSize(18);
		optionText.setFillColor(sf::Color::Black);
		optionText.setPosition(posx + 10, posy + (i + 1) * height + 5);
		optionsTexts.push_back(optionText);
	}
}

std::string UI::Dropdown::getSelection() const {
	return selectedOption;  // Ahora devuelve la opción almacenada
}

void UI::Dropdown::handleEvent(const sf::Event& event) {
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

		if (dropdownBox.getGlobalBounds().contains(mousePos)) {
			isOpen = !isOpen; // Alternar entre abierto/cerrado
		}
		else if (isOpen) {
			for (size_t i = 0; i < optionsBoxes.size(); i++) {
				if (optionsBoxes[i].getGlobalBounds().contains(mousePos)) {
					selectedOption = optionsList[i];  // Guarda la opción seleccionada
					textBox.setString(selectedOption); // Actualiza el texto mostrado
					isOpen = false;
					break;
				}
			}
		}
	}
}

void UI::Dropdown::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(dropdownBox);
	target.draw(textBox);

	if (isOpen) { // Si está desplegado, dibujar las opciones
		for (const auto& box : optionsBoxes) {
			target.draw(box);
		}
		for (const auto& text : optionsTexts) {
			target.draw(text);
		}
	}
}

