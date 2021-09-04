#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class userShapes
{
private:
    sf::RectangleShape shape;
    std::vector <sf::RectangleShape> shapes;
    bool ispressed;
    bool ispos;

public:
    userShapes();

    //Functions
    void update(sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

    std::vector<sf::RectangleShape>& getShapes();
};

