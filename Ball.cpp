#include "stdafx.h"
#include "Ball.h"


bool Ball::checkTopDownCollision()
{
	if (c_shape.getGlobalBounds().getPosition().y < 0 ||
		c_shape.getGlobalBounds().getPosition().y > 600 - c_shape.getGlobalBounds().height) {

		dir.y = -dir.y;
		if (dir.y < 0) {
			dir.y--;
		}
		else {
			dir.y++;
		}
		reboundCount++;
		if (dir.x > 0) {
			return true;
		}
		
	}
	return false;

}

bool Ball::checkCollisionPlayer(sf::FloatRect rect)
{
	if (c_shape.getGlobalBounds().intersects(rect)) {
		reboundCount++;
		return true;

	}
	return false;
}

//public scope
Ball::Ball()
{
	c_shape.setPosition(450, 300);
	c_shape.setRadius(5.f);

	speed = 7.f;
	dir = sf::Vector2f{ -speed, 1.f };
	
	reboundCount = 0;
}

sf::Vector2f Ball::getPos() const
{
	return c_shape.getPosition();
}

sf::Vector2f Ball::getDir() const
{
	return dir;
}

void Ball::update()
{
	c_shape.move(dir);
}

void Ball::updateDir()
{
	//reverse ball direction 
	dir.x = -(dir.x);
	//get random ball y direction
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	// 50% change to change y dir from up to down and down to up
	int x = rand() % (2 - 1 + 1) + 1;
	if (x == 1) {
		dir.y = -r;
	}
	else {
		dir.y = r;
	}
	// TODO : max speed is around 30 rebounds 
	if (dir.y < 0) {
		dir.y -= reboundCount / static_cast<float>(10);
	}
	else {
		dir.y += reboundCount / static_cast<float>(10);
	}

	if (dir.x < 0) {
		dir.x -= reboundCount / static_cast<float>(25);
	}
	else {
		dir.x += reboundCount / static_cast<float>(25);
	}
	
}

void Ball::reset()
{
	std::cout << reboundCount << '\n';

	dir = sf::Vector2f{ -speed, 0.f };

	reboundCount = 0;

	c_shape.setPosition(450, 300);

}

void Ball::render(sf::RenderTarget& target)
{
	target.draw(c_shape);
}
