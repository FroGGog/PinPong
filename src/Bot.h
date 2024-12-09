#pragma once


class Bot
{

private:

	float speed;

	sf::Vector2f dir;
	
	sf::RectangleShape bot_shape;

	sf::RectangleShape collBox;


public:

	Bot();

	void updateBordersColl();

	sf::FloatRect getFRect() const;
	sf::FloatRect getColliderRect() const;

	void update(sf::CircleShape destPoint);

	void render(sf::RenderTarget& target);

	void reset();

};

