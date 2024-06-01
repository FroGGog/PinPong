#pragma once
#include "Player.h"

class Ball
{
private:

	sf::CircleShape c_shape;

	sf::Vector2f dir;
	float speed;
	int reboundCount;

	

public:

	Ball();

	sf::Vector2f getPos() const;
	sf::Vector2f getDir() const;

	void update();
	bool checkCollisionPlayer(sf::FloatRect rect);
	bool checkTopDownCollision();
	void updateDir();

	void reset();

	void render(sf::RenderTarget& target);
};

