#pragma once


// Create a text
// sf::Text text(L"ERROR", font, 25);

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>




namespace UI {
	
	
class Button : public sf::Drawable {
public: 
	Button(float posx, float posy, float height, float width, const std::string& Label,	
		sf::Color onColor = sf::Color::Green, sf::Color offColor = sf::Color::Red );

	void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

	bool getState() const; // Retorna si est� activo o no
		
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;	// M�todo para dibujar en pantalla (override de sf::Drawable)
private:

	sf::Font font;
	sf::Text textBox;
	sf::RectangleShape buttonBox;  
	sf::Color activeColor;
	sf::Color inactiveColor;
	bool isActive = false;  


};

	

class Dropdown : public sf::Drawable {
public:
	Dropdown(std::vector<std::string> optionsList, float posx, float posy, float height, float width);
	std::string getSelection();
	void handleEvent(const sf::Event& event); // Manejo de eventos
	//void resize();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;	// M�todo para dibujar en pantalla (override de sf::Drawable)
private:
	sf::Font font;
	sf::Text textBox;
	sf::RectangleShape dropdownBox;
	std::vector<std::string> optionsList;
	std::vector<sf::RectangleShape> optionsBoxes;
	std::vector<sf::Text> optionsTexts;
	float posx, posy, height, width;
	bool isOpen = false;
	 
};

}