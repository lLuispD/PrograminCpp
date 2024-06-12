
#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1000), "SFML works!");
    sf::CircleShape shape(25.f);
    shape.setFillColor(sf::Color::Green);
    


    int xf = 0, yf = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        shape.setPosition(100, 220);
        window.display();
        //_sleep(100);
    }

    return 0;
}