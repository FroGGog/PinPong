#pragma once


class Bot
{

private:

	float speed;

	sf::Vector2f dir;
	
	sf::RectangleShape bot_shape;


public:

	Bot();

	void updateBordersColl();

	sf::FloatRect getFRect() const;

	void update(std::shared_ptr<sf::CircleShape> destPoint);

	void render(sf::RenderTarget& target);


};

