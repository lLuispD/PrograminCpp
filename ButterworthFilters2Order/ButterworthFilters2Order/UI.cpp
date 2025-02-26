#include "UI.hpp" 

static const std::string dirFont = "C:/Users/_pdd/source/PrograminCpp/SFML_TUTOS/Fonts/arial.ttf";

 
UI::Dropdown::Dropdown(std::vector<std::string> optionsList, float posx, float posy, float height, float width)
	: optionsList(optionsList), posx(posx), posy(posy), height(height), width(width), selectedOption(optionsList[0]) {

	font.loadFromFile(dirFont);

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
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (event.type == sf::Event::MouseButtonPressed) {
		if (buttonBox.getGlobalBounds().contains(mousePos)) {
			isPressed = true;
			buttonBox.setFillColor(activeColor);
			if (callback) callback();
		}
	}
	else if (event.type == sf::Event::MouseButtonReleased) {
		isPressed = false;
		buttonBox.setFillColor(inactiveColor);
	}
}

// Asigna una función a ejecutar
void UI::Button::setCallback(std::function<void()> callback) {
	this->callback = callback;
}

// Devuelve el estado del botón
bool UI::Button::getState() const {
	return isPressed;
}

// Dibujar en pantalla
void UI::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(buttonBox, states);
	target.draw(textBox, states);
}

 

// Constructor
UI::Texto::Texto(const std::string& texto, float x, float y, unsigned int tamanio, sf::Color color) {
	// Intentamos cargar la fuente predeterminada (Asegúrate de tener la fuente en tu proyecto)
	if (!fuente.loadFromFile(dirFont)) {
		std::cerr << "No se pudo cargar la fuente!" << std::endl;
	}

	// Establecer el texto, tamaño de fuente y color
	this->texto.setString(texto);
	this->texto.setFont(fuente);
	this->texto.setCharacterSize(tamanio);
	this->texto.setFillColor(color);
	this->texto.setPosition(x, y);
}

// Cambiar el texto
void UI::Texto::setTexto(const std::string& nuevoTexto) {
	texto.setString(nuevoTexto);
}

// Cambiar la posición
void UI::Texto::setPosicion(float x, float y) {
	texto.setPosition(x, y);
}

// Cambiar el color
void UI::Texto::setColor(sf::Color color) {
	texto.setFillColor(color);
}

// Implementación de la función draw heredada de sf::Drawable
void UI::Texto::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(texto, states);  // Dibuja el texto en la ventana
}



// Constructor unificado
UI::TextBox::TextBox(float x, float y, float width, float height, bool numbersOnly)
	: isActive(false), onlyNumbers(numbersOnly), cursorPos(0), cursorVisible(true)
{
	box.setSize(sf::Vector2f(width, height));
	box.setPosition(x, y);
	box.setFillColor(sf::Color::White);
	box.setOutlineThickness(2);
	box.setOutlineColor(sf::Color::Black);

	// Carga de fuente (asegúrate de que 'resources/arial.ttf' exista)
	if (!font.loadFromFile(dirFont)) {
		std::cerr << "Error: No se pudo cargar la fuente.\n";
	}

	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Black);
	text.setPosition(x + 5, y + 5);

	cursor.setSize(sf::Vector2f(2, text.getCharacterSize()));
	cursor.setFillColor(sf::Color::Black);
	cursor.setPosition(text.getPosition().x, text.getPosition().y);

	enterCallback = nullptr;
}

// Dibuja el cuadro de texto y el cursor
void UI::TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(box, states);
	target.draw(text, states);
	if (isActive && cursorVisible) {
		target.draw(cursor, states);
	}
}

// Manejo de eventos
void UI::TextBox::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		isActive = box.getGlobalBounds().contains(mousePos);
		box.setOutlineColor(isActive ? sf::Color::Blue : sf::Color::Black);
		if (isActive)
			cursorTimer.restart();
	}

	if (isActive) {
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
					if (isdigit(enteredChar) || enteredChar == '.' || enteredChar == '-') {
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

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Left && cursorPos > 0) {
				cursorPos--;
			}
			else if (event.key.code == sf::Keyboard::Right && cursorPos < inputString.size()) {
				cursorPos++;
			}
			else if (event.key.code == sf::Keyboard::Enter) {
				if (enterCallback)
					enterCallback();  // Ejecuta la función asignada
			}
		}

		// Actualizar la posición del cursor
		float cursorOffset = text.findCharacterPos(cursorPos).x;
		cursor.setPosition(cursorOffset, text.getPosition().y);
	}
}

// Alterna la visibilidad del cursor (efecto parpadeo)
void UI::TextBox::updateCursor() {
	if (cursorTimer.getElapsedTime().asSeconds() > 0.5f) {
		cursorVisible = !cursorVisible;
		cursorTimer.restart();
	}
}

// Devuelve el texto ingresado
std::string UI::TextBox::getText() const {
	return inputString;
}

// Devuelve el contenido como número flotante
float UI::TextBox::getFloat() const {
	try {
		return std::stof(inputString);
	}
	catch (...) {
		return 0.0f;
	}
}

// Configuración de la fuente
void UI::TextBox::setFont(const sf::Font& font) {
	this->font = font;
	text.setFont(this->font);
}

// Configuración del color del texto
void UI::TextBox::setTextColor(const sf::Color& color) {
	text.setFillColor(color);
}

// Configuración del color de fondo del cuadro
void UI::TextBox::setBoxColor(const sf::Color& color) {
	box.setFillColor(color);
}

// Configuración del color del borde cuando está activo
void UI::TextBox::setActiveColor(const sf::Color& color) {
	if (isActive) {
		box.setOutlineColor(color);
	}
}

// Única función para actualizar el contenido del TextBox
void UI::TextBox::setText(const std::string& newText) {
	inputString = newText;
	text.setString(inputString);
	cursorPos = static_cast<int>(inputString.size());
	float cursorOffset = text.findCharacterPos(cursorPos).x;
	cursor.setPosition(cursorOffset, text.getPosition().y);
}

// Asigna la función callback para cuando se presiona Enter
void UI::TextBox::setOnEnterPressed(std::function<void()> callback) {
	enterCallback = callback;
}
