#include "userShapes.h"

// Constructor
userShapes::userShapes()
{
    ispressed = false,
    ispos = false;

    sf::RectangleShape floor;
    floor.setPosition(0, 900);
    floor.setSize(sf::Vector2f(1000, 100));
    floor.setRotation(-20);
    shapes.push_back(floor);
}

// Adds a line to userShapes
void userShapes::update(sf::RenderWindow& window)
{
    // left click...
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        ispressed = true;
    // Initiate line pos
    if (ispressed & !sf::Mouse::isButtonPressed(sf::Mouse::Left) & !ispos)
    {
        ispressed = false;
        ispos = true;
        shape.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
    }
    // Predict line to be drawn
    int delta_x = shape.getPosition().x - sf::Mouse::getPosition(window).x;
    int delta_y = shape.getPosition().y - sf::Mouse::getPosition(window).y;
    int csize = sqrt(delta_x * delta_x + delta_y * delta_y);
    shape.setSize(sf::Vector2f(csize, 5));
    float crot = atan2(delta_y, delta_x);
    shape.setRotation(180 + crot * 180 / 3.14159265358979323846);
    // Add new line to the vector
    if (ispos & ispressed & !sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        shapes.push_back(shape);
        shape.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
        ispressed = false;
    }
    // Reinitialize process
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) & ispos)
        ispos = false;
}

void userShapes::render(sf::RenderWindow& window)
{
    if (ispos)
        window.draw(shape);
    for (auto& x : shapes)
        window.draw(x);
}

std::vector<sf::RectangleShape>& userShapes::getShapes()
{
    return shapes;
}
