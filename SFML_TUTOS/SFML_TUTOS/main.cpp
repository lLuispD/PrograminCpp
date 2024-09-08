/*
*	NuGet: SFML_2019
*/

#include <iostream>
#include <SFML/Graphics.hpp>


int main() {
	
	sf::RenderWindow window(sf::VideoMode(1500, 800), "Space inveaders");	// CREAR UNA VENTANA (X,Y) 
	window.setFramerateLimit(60);		// LIMITE FPS
	
	// Creacion de un Cuadrado
	sf::RectangleShape rectangle(sf::Vector2f(100, 50));
	rectangle.setOrigin(sf::Vector2f(-20, -20));
	

	// Creacion de linea.
	sf::Vertex line[] = {
		sf::Vertex(sf::Vector2f(45,100)),	// X1, Y1
		sf::Vertex(sf::Vector2f(200,100))	// X2, Y2
	};

	// Declare and load a font	
	sf::Font font;
	font.loadFromFile("C:/Users/luisp/source/C++/SFML_TUTOS/fonts/arial.ttf");

	// Create a text
	sf::Text text(L"ERROR", font,25);
	
	text.setOrigin(-1000,-500);
	text.setStyle(sf::Text::Italic);
	text.setFillColor(sf::Color::Red);

	


	// Bucle Principal
	while (window.isOpen()) {

		sf::Event event;				//	Crear evento 
		// Cerrar ventana cuando eveto -> cerrar ventana
		while (window.pollEvent(event)) {
			switch (event.type) {
			// cerrar ventana
			case  sf::Event::Closed	:		window.close();	break;
			// mover cursor
			case sf::Event::MouseMoved :	// movimiento de mouse
				// imprimir en consola las coordenadas
				system("cls"); 
				std::cout << "coordenadas:" << event.mouseMove.x << " , " << event.mouseMove.y << std::endl;
				text.setString("pos");
				
				break;
			}

		}
		// Update
		window.clear();			// Limpiar pantalla
		window.draw(rectangle);
		window.draw(text);
		window.draw(line,2,sf::Lines);
		window.display();		// dibujar pantalla
	}
	return 0;
}
