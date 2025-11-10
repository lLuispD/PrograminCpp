#pragma once


#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <cctype>


namespace UI {

	class Text : public sf::Drawable {
	public:
		// Constructores
		Text();
		Text(const std::string& texto, float x, float y, unsigned int tamanio, sf::Color color = sf::Color::Black, float RotationAngle = 0);

		// Métodos para modificar el texto
		void setText(const std::string& newTxt);
		void setPosicion(float x, float y);
		void setZise(unsigned int newSize);
		void setColor(sf::Color color);
		void rotateTo(float Angle);


	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Text texto;  // Objeto que representa el texto
		sf::Font fuente;  // Fuente usada para el texto
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


}