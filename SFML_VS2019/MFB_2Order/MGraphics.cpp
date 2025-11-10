#include "SFML_MFB.hpp"
#include <sstream>
#include <iomanip>

#include    <functional>           // Para std::function 
#include    <iostream>

#include <windows.h>
#include <commdlg.h>
#include <string> 


#define fontAddress "../Fonts/arial.ttf"


/******************************************************************* TEXTO *******************************************************************/


GUI::Txt::Txt() {
    loadFont(fontAddress);
}

bool GUI::Txt::loadFont(const std::string& fontPath) {
    if (font.loadFromFile(fontPath)) {
        text.setFont(font);
        fontLoaded = true;
        return true;
    }
    std::cerr << "no se cargo la fuente";
    return false;
}

void GUI::Txt::setText(const std::string& str) {
    if (!fontLoaded) {
        throw std::runtime_error("No se ha cargado ninguna fuente");
    }
    text.setString(str);
}

void GUI::Txt::setCharacterSize(unsigned int size) {
    text.setCharacterSize(size);
}

void GUI::Txt::setPosition(float x, float y) {
    text.setPosition(x, y);
}

void GUI::Txt::setRotationAngle(float RotationAngle) {
    text.setRotation(-1 * RotationAngle);
}

void GUI::Txt::setSize(unsigned int size) {
    text.setCharacterSize(size);
}

sf::Vector2f GUI::Txt::getBounds() {
    sf::FloatRect bounds = text.getLocalBounds();
    return sf::Vector2f(bounds.width, bounds.height);
}

void GUI::Txt::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!fontLoaded) {
        throw std::runtime_error("Intentando dibujar sin fuente cargada");
    }
    target.draw(text, states);
}

/****************************************************************************************************************************/

GUI::Btn::Btn() {
    setSize(100, 12);       // Tamaño predeterminado
    setColorsOnOff(sf::Color(85, 85, 85), sf::Color(0, 170, 170));
    _BtnBox.setFillColor(inactiveColor);
}

void GUI::Btn::setPosition(float x, float y) {
    _BtnBox.setPosition(x, y);
    _TextBox.setPosition(
        x + (_BtnBox.getGlobalBounds().width - _TextBox.getBounds().x) * .5f,
        y + (_BtnBox.getGlobalBounds().height - _TextBox.getBounds().y) * .3f
    );

}

void GUI::Btn::setRotationAngle(float angle) {
    _BtnBox.setRotation(angle);
    _TextBox.setRotationAngle(angle);
}

void GUI::Btn::setSize(float width, float height) {
    _BtnBox.setSize({ width, height });
}

void GUI::Btn::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (event.type == sf::Event::MouseButtonPressed) {
        if (_BtnBox.getGlobalBounds().contains(mousePos)) {
            isPressed = true;
            _BtnBox.setFillColor(activeColor);
            if (callback) {
                callback();
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        isPressed = false;
        _BtnBox.setFillColor(inactiveColor);
    }
}

void GUI::Btn::setCallback(std::function<void()> callback) {
    this->callback = callback;
}

bool GUI::Btn::getState() const {
    return isPressed;
}

void GUI::Btn::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_BtnBox, states);
    target.draw(_TextBox, states);
}

void GUI::Btn::setText(const std::string& Text) {
    _TextBox.setText(Text);
    _TextBox.setCharacterSize(20);

}

void GUI::Btn::setColorsOnOff(sf::Color onColor, sf::Color offColor) {
    activeColor = onColor;
    inactiveColor = offColor;
}




// Constructor
GUI::TextBox::TextBox(float x, float y, float width, float height, bool numbersOnly)
    : isActive(false), onlyNumbers(numbersOnly), cursorPos(0), cursorVisible(true)
{
    box.setSize(sf::Vector2f(width, height));
    box.setPosition(x, y);
    box.setFillColor(sf::Color::White);
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::Black);

    if (!font.loadFromFile(fontAddress)) {
        std::cerr << "Error: No se pudo cargar la fuente.\n";
    }

    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 5, y + 5);

    cursor.setSize(sf::Vector2f(2, text.getCharacterSize()));
    cursor.setFillColor(sf::Color::Black);
    cursor.setPosition(text.getPosition().x, text.getPosition().y);
}

// Dibuja el cuadro de texto y el cursor
void GUI::TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(box, states);
    target.draw(text, states);
    if (isActive && cursorVisible) {
        target.draw(cursor, states);
    }
}

// Manejo de eventos
void GUI::TextBox::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        isActive = box.getGlobalBounds().contains(mousePos);

        box.setOutlineColor(isActive ? sf::Color::Blue : sf::Color::Black);
        if (isActive) cursorTimer.restart();
    }

    if (isActive) {
        // Entrada de texto
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8) { // Backspace
                if (cursorPos > 0) {
                    inputString.erase(cursorPos - 1, 1);
                    cursorPos--;
                }
            }
            else if (event.text.unicode < 128) {
                char enteredChar = static_cast<char>(event.text.unicode);

                if (onlyNumbers) {
                    if (std::isdigit(enteredChar) || enteredChar == '.' || enteredChar == '-') {
                        inputString.insert(cursorPos, 1, enteredChar);
                        cursorPos++;
                    }
                }
                else {
                    inputString.insert(cursorPos, 1, enteredChar);
                    cursorPos++;
                }
            }

            text.setString(inputString);
        }

        // Movimiento del cursor con flechas y Enter
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Left && cursorPos > 0) {
                cursorPos--;
            }
            if (event.key.code == sf::Keyboard::Right && cursorPos < inputString.size()) {
                cursorPos++;
            }

            // --- Nuevo: Detectar Enter ---
            if (event.key.code == sf::Keyboard::Enter) {
                // Llamar a la función callback si está configurada
                if (onEnterCallback) {
                    onEnterCallback(inputString);
                }
                isActive = false;
                box.setOutlineColor(sf::Color::Black);
            }
        }

        // Actualizar la posición del cursor
        float cursorOffset = text.findCharacterPos(cursorPos).x;
        cursor.setPosition(cursorOffset, text.getPosition().y);
    }
}

// Alternar visibilidad del cursor (parpadeo)
void GUI::TextBox::updateCursor() {
    if (cursorTimer.getElapsedTime().asSeconds() > 0.5f) {
        cursorVisible = !cursorVisible;
        cursorTimer.restart();
    }
}

// Devuelve el texto ingresado (string)
std::string GUI::TextBox::getText() const {
    return inputString;
}

// Devuelve el texto como número flotante
float GUI::TextBox::getFloat() const {
    try {
        return std::stof(inputString);
    }
    catch (...) {
        return 0.0f;
    }
}

// Configuración de colores y fuente
void GUI::TextBox::setFont(const sf::Font& font) {
    this->font = font;
    text.setFont(this->font);
}

void GUI::TextBox::setTextColor(const sf::Color& color) {
    text.setFillColor(color);
}

void GUI::TextBox::setBoxColor(const sf::Color& color) {
    box.setFillColor(color);
}

void GUI::TextBox::setActiveColor(const sf::Color& color) {
    if (isActive) {
        box.setOutlineColor(color);
    }
}

// --- Nuevo: Asignar la función callback para Enter ---
void GUI::TextBox::setOnEnterCallback(const std::function<void(const std::string&)>& callback) {
    onEnterCallback = callback;
}




/******************************************************************* DROPDOWN *******************************************************************/

GUI::Dropdown::Dropdown(std::vector<std::string> optionsList, float posx, float posy, float height, float width)
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

std::string GUI::Dropdown::getSelection() const {
	return selectedOption;  // Ahora devuelve la opción almacenada
}

void GUI::Dropdown::handleEvent(const sf::Event& event) {
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

void GUI::Dropdown::draw(sf::RenderTarget& target, sf::RenderStates states) const {
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

