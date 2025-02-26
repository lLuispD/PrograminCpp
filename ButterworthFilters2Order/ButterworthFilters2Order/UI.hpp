#pragma once

// Create a text
// sf::Text text(L"ERROR", font, 25);

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <cctype>


namespace UI {


	class Button : public sf::Drawable {
	public:
		Button(float posx, float posy, float height, float width, const std::string& Label,
			sf::Color onColor = sf::Color::Green, sf::Color offColor = sf::Color::Red);

		void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

		void setCallback(std::function<void()> callback); // Asigna una función a ejecutar

		bool getState() const; // Retorna si está activo o no

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Font font;
		sf::Text textBox;
		sf::RectangleShape buttonBox;
		sf::Color activeColor;
		sf::Color inactiveColor;
		bool isPressed = false;
		std::function<void()> callback;
	};

	class Dropdown : public sf::Drawable {
	public:
		Dropdown(std::vector<std::string> optionsList, float posx, float posy, float height, float width);
		std::string getSelection() const; // Ahora es const
		void handleEvent(const sf::Event& event);

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Font font;
		sf::Text textBox;
		sf::RectangleShape dropdownBox;
		std::vector<std::string> optionsList;
		std::vector<sf::RectangleShape> optionsBoxes;
		std::vector<sf::Text> optionsTexts;
		float posx, posy, height, width;
		bool isOpen = false;

		std::string selectedOption; // Almacena la opción seleccionada
	};

	class Texto : public sf::Drawable {
	public:
		// Constructor
		Texto(const std::string& texto, float x, float y, unsigned int tamanio, sf::Color color = sf::Color::Black);

		// Métodos para modificar el texto
		void setTexto(const std::string& nuevoTexto);
		void setPosicion(float x, float y);
		void setColor(sf::Color color);

	protected:
		// Función para dibujar el texto, implementada de forma obligatoria por heredar de sf::Drawable
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Text texto;  // El objeto que representa el texto
		sf::Font fuente;  // La fuente usada para el texto
	};

	class TextBox : public sf::Drawable {
	private:
		sf::RectangleShape box;
		sf::Text text;
		sf::Font font;
		bool isActive;
		bool onlyNumbers;
		std::string inputString;
		int cursorPos;

		sf::RectangleShape cursor;
		sf::Clock cursorTimer;
		bool cursorVisible;

		// Callback para la tecla Enter
		std::function<void()> enterCallback;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	public:
		TextBox(float x, float y, float width, float height, bool numbersOnly = false);

		void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
		void updateCursor();

		std::string getText() const;
		float getFloat() const;

		void setFont(const sf::Font& font);
		void setTextColor(const sf::Color& color);
		void setBoxColor(const sf::Color& color);
		void setActiveColor(const sf::Color& color);

		// *** ÚNICA FUNCIÓN PARA ACTUALIZAR EL TEXTO ***
		void setText(const std::string& newText);

		// Asigna la función que se llamará al presionar Enter
		void setOnEnterPressed(std::function<void()> callback);
	};

 




}