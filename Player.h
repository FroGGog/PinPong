#pragma once


class Player
{
private:


	sf::Keyboard::Key up, down;
	sf::Vector2f dir;
	float speed = 7.f;

	sf::RectangleShape p_shape;
	sf::Vector2f startPos;

	void updatePlayer();

	void updateBordersColl();


public:

	Player(sf::Vector2f pos, sf::Keyboard::Key up, sf::Keyboard::Key down);

	sf::FloatRect getFRect() const;

	void update();

	void reset();
	
	void render(sf::RenderTarget& target);


};

