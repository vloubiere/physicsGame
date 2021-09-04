#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Collision.h"





class physicalObject
{
private:
	sf::CircleShape shape;
	sf::CircleShape closest;
	sf::Vector2f velocity;
	sf::Clock clock;
	float dt;
	float acceleration;
	float velocityMin;
	float velocityMax;
	float drag;
	float gravity;
	float gravityMax;
	bool touch;
	float jumpSpeed;
	int pnpoly(int nvert, float* vertx, float* verty, float testx, float testy);

public:
	physicalObject();

	//Functions
	void update(std::vector<sf::RectangleShape>& obstacles);
	void render(sf::RenderWindow& window);
};

