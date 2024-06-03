#include "stdafx.h"
#include "Player.h"

Player::Player(sf::Vector2f pos, sf::Keyboard::Key up, sf::Keyboard::Key down)
{

	this->up = up;
	this->down = down;

	p_shape.setPosition(pos);
	startPos = pos;
	p_shape.setSize(sf::Vector2f{ 10.f, 70.f });

	dir = sf::Vector2f{ 0,0 };

}

sf::FloatRect Player::getFRect() const
{
	return p_shape.getGlobalBounds();
}

void Player::update()
{

	updatePlayer();

	updateBordersColl();

	p_shape.move(dir);
}

void Player::reset()
{
	p_shape.setPosition(startPos);
	dir = sf::Vector2f{ 0, 0 };
}


void Player::render(sf::RenderTarget& target)
{
	target.draw(p_shape);
}

void Player::updatePlayer()
{
	if (sf::Keyboard::isKeyPressed(up)) {
		dir.y = -speed;
	}
	else if (sf::Keyboard::isKeyPressed(down)) {
		dir.y = speed;
	}
	else {
		dir.y = 0;

	}
}

void Player::updateBordersColl()
{
	//check borders
	if (p_shape.getGlobalBounds().getPosition().y + p_shape.getGlobalBounds().height > 600) {
		p_shape.setPosition(p_shape.getGlobalBounds().getPosition().x, 600 - p_shape.getGlobalBounds().height);
		return;
	}
	if (p_shape.getGlobalBounds().getPosition().y < 0) {
		p_shape.setPosition(p_shape.getGlobalBounds().getPosition().x, 0);
		return;
	}
}
