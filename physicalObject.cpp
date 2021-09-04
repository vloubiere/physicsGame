#include "physicalObject.h"

int physicalObject::pnpoly(int nvert, float *vertx, float* verty, float testx, float testy)
{
	int i, j, c = 0;
	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((verty[i] > testy) != (verty[j] > testy)) &&
			(testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
			c = !c;
	}
	return c;
}

physicalObject::physicalObject()
{
	shape.setPosition(800, 100);
	shape.setRadius(50);
	shape.setPointCount(99);
	closest.setRadius(10);
	closest.setFillColor(sf::Color::Cyan);
	acceleration = 0;
	velocityMax = 30;
	dt = clock.getElapsedTime().asSeconds();
	velocityMin = 2;
	drag = 0.99f;
	gravity = 15.f;
	gravityMax = 25.f;
	jumpSpeed = 0;
	touch = false;
}


void physicalObject::update(std::vector<sf::RectangleShape>& obstacles)
{
	dt = clock.getElapsedTime().asSeconds();
	clock.restart();
	
	// ACCELERATION
	velocity.y += -dt * acceleration;
	// LIMIT velocity
	if (std::abs(velocity.y) > velocityMax)
		velocity.y = velocityMax;

	// GRAVITY
	velocity.y += (dt * gravity);
	if (std::abs(velocity.y) > gravityMax)
		velocity.y = gravityMax; 

	// COLLISION
	// Extract obstacles whose bounding boxes intersect shape
	std::vector<sf::RectangleShape> intersectingShapes;
	for (int i = 0; i < obstacles.size(); i++)
	{
		bool boundingBoxIntersect = shape.getGlobalBounds().intersects(obstacles[i].getGlobalBounds());
		// If bounding boxes do not intersect, remove the current element from intersectinShapes vector
		if (boundingBoxIntersect)
		{
			intersectingShapes.push_back(obstacles[i]);
		}
	}
	// Comput precise collision for shapes whose bounding boxes do intersect
	int checkTouch = 0;
	if (intersectingShapes.size() > 0)
	{
		float vertx[4] = { intersectingShapes[0].getTransform().transformPoint(intersectingShapes[0].getPoint(0)).x,
		intersectingShapes[0].getTransform().transformPoint(intersectingShapes[0].getPoint(1)).x,
		intersectingShapes[0].getTransform().transformPoint(intersectingShapes[0].getPoint(2)).x,
		intersectingShapes[0].getTransform().transformPoint(intersectingShapes[0].getPoint(3)).x };
		float verty[4] = { intersectingShapes[0].getTransform().transformPoint(intersectingShapes[0].getPoint(0)).y,
		intersectingShapes[0].getTransform().transformPoint(intersectingShapes[0].getPoint(1)).y,
		intersectingShapes[0].getTransform().transformPoint(intersectingShapes[0].getPoint(2)).y,
		intersectingShapes[0].getTransform().transformPoint(intersectingShapes[0].getPoint(3)).y };
		float testx = shape.getTransform().transformPoint(shape.getPoint(50)).x;
		float testy = shape.getTransform().transformPoint(shape.getPoint(50)).y;
		checkTouch = pnpoly(4, vertx, verty, testx, testy);
	}
	
	// REBOUND UPON COLLISION
	if (checkTouch==1 && !touch)
	{
		velocity.y = -0.6f * velocity.y;
		//velocity.y = -sqrt(velocity.y * velocity.y);
		touch = true;
	}
	else
		touch = false;
	
	// DECELERATION
	velocity.y *= drag;
	// Clip friction deceleration
	if (std::abs(velocity.y) < velocityMin && checkTouch == 1)
		velocity.y = 0.f; 

	shape.move(velocity);
}

void physicalObject::render(sf::RenderWindow& window)
{
	window.draw(shape);
	window.draw(closest);
}
