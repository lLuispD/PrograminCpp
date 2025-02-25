#include "UI.hpp"
 
void clickButton() {

}


int main(void) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Desplegable y boton");

    std::vector <std::string> filterOptions = { "Filtro Paso Bajo", "Filtro Paso Alto" };
    UI::Dropdown filterTypes(filterOptions, 200, 200, 30, 150);

    std::vector <std::string> cUnitys = { " F" ,"mF", "uF","nF","pF" };
    UI::Dropdown capLevel(cUnitys, 500, 200, 30, 50);

    UI::Button button(400, 400, 50, 100, "Click Me",sf::Color(22, 160, 141), sf::Color(32, 200, 228));
     
    // Crear ventana

    button.setCallback([]() {
        std::cout << "¡Botón presionado!" << std::endl;
        });

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            filterTypes.handleEvent(event); // Manejo de eventos del Dropdown
            capLevel.handleEvent(event);
            button.handleEvent(event, window); 
        }

        window.clear(sf::Color::White);
        window.draw(filterTypes); // Dibujar el Dropdown directamente
        window.draw(capLevel);
        window.draw(button);
        window.display();
    }


    return 0;
}



 
