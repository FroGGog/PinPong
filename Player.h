#pragma once


class Player
{
private:


	sf::Keyboard::Key up, down;
	sf::Vector2f dir;
	float speed = 5.f;
	bool botPlayer;

	sf::RectangleShape p_shape;

	void updatePlayer();

	void updateBordersColl();


public:

	Player(sf::Vector2f pos, sf::Keyboard::Key up, sf::Keyboard::Key down);

	sf::FloatRect getFRect() const;

	void update();
	
	void render(sf::RenderTarget& target);


};

