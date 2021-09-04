#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include "userShapes.h"
#include "physicalObject.h"

int main()
{
    // VARIABLES
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    window.setFramerateLimit(60);
    userShapes shapes;
    physicalObject circle;

    // GAME LOOP
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // UPDATE
        shapes.update(window);
        circle.update(shapes.getShapes());

        // RENDERING
        window.clear(sf::Color(100, 0, 0, 255));
        shapes.render(window);
        circle.render(window);
        window.display();
    }
    return 0;
}