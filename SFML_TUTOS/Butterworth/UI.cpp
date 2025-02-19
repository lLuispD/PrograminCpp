#include "UI.hpp" 

std::string dirFont = "C:/Users/_pdd/source/PrograminCpp/SFML_TUTOS/Fonts/arial.ttf";

UI::Dropdown::Dropdown(std::vector<std::string> optionsList, float posx, float posy, float height, float width) 
	: optionsList(optionsList), posx(posx),posy(posy), height(height), width(width) {

	font.loadFromFile(dirFont);

	dropdownBox.setSize(sf::Vector2f(width, height));
	dropdownBox.setPosition(posx, posy);
	dropdownBox.setFillColor(sf::Color::White);
	dropdownBox.setOutlineColor(sf::Color::Black);
	dropdownBox.setOutlineThickness(2);

	textBox.setFont(font);
	textBox.setString(optionsList[0]);
	textBox.setCharacterSize(18);
	textBox.setFillColor(sf::Color::Black);
	textBox.setPosition(posx + 10, posy + 5);

	for( size_t i = 0 ; i < optionsList.size() ; i++ ) {
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

std::string UI::Dropdown::getSelection(){
	// Obtener la opción seleccionada 
	return textBox.getString();
}

void UI::Dropdown::handleEvent(const sf::Event& event){ 
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

		if (dropdownBox.getGlobalBounds().contains(mousePos)) {
			isOpen = !isOpen; // Alternar entre abierto/cerrado
		}
		else if (isOpen) {
			for (size_t i = 0; i < optionsBoxes.size(); i++) {
				if (optionsBoxes[i].getGlobalBounds().contains(mousePos)) {
					textBox.setString(optionsList[i]); // Seleccionar opción
					isOpen = false;
					break;
				}
			}
		}
	}
}


// Método para dibujar (se llama automáticamente con window.draw())
void UI::Dropdown::draw(sf::RenderTarget& target, sf::RenderStates states) const{
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
 



 

// Constructor
UI::Button::Button(float posx, float posy, float height, float width, const std::string& label,
	sf::Color onColor, sf::Color offColor)
	: activeColor(onColor), inactiveColor(offColor) {

	// Cargar fuente
	font.loadFromFile(dirFont);
	

	// Configurar el botón
	buttonBox.setSize(sf::Vector2f(width, height));
	buttonBox.setPosition(posx, posy);
	buttonBox.setFillColor(inactiveColor);

	// Configurar el texto
	textBox.setFont(font);
	textBox.setString(label);
	textBox.setCharacterSize(20);
	textBox.setFillColor(sf::Color::White);
	textBox.setPosition(
		posx + (width - textBox.getLocalBounds().width) / 2.5f,
		posy + (height - textBox.getLocalBounds().height) / 2.5f
	);
}

// Manejo de eventos
void UI::Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		if (buttonBox.getGlobalBounds().contains(mousePos)) {
			isActive = !isActive;
			buttonBox.setFillColor(isActive ? activeColor : inactiveColor);
		}
	}
}

// Devuelve el estado del botón
bool UI::Button::getState() const {
	return isActive;
}

// Dibujar en pantalla
void UI::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(buttonBox, states);
	target.draw(textBox, states);
}
