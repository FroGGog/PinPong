#include "stdafx.h"
#include "Bot.h"

Bot::Bot()
{
	
	speed = 7.f;

	dir = sf::Vector2f{ 0, 0 };

	bot_shape.setSize(sf::Vector2f{ 10.f, 70.f });
	bot_shape.setPosition(880, 300);

	collBox.setSize(sf::Vector2f{ 10.f, 10.f });
	collBox.setPosition(bot_shape.getPosition().x, bot_shape.getPosition().y + bot_shape.getGlobalBounds().height / 2);
	collBox.setFillColor(sf::Color::Green);

}

void Bot::updateBordersColl()
{
	//check borders
	if (bot_shape.getGlobalBounds().getPosition().y + bot_shape.getGlobalBounds().height > 600) {
		bot_shape.setPosition(bot_shape.getGlobalBounds().getPosition().x, 600 - bot_shape.getGlobalBounds().height);
		return;
	}
	if (bot_shape.getGlobalBounds().getPosition().y < 0) {
		bot_shape.setPosition(bot_shape.getGlobalBounds().getPosition().x, 0);
		return;
	}
}

void Bot::update(sf::CircleShape destPoint)
{
	updateBordersColl();
	//if bot is already at end pos
	if (collBox.getGlobalBounds().intersects(destPoint.getGlobalBounds())) {
		dir.y = 0;
		return;
	}

	if (collBox.getPosition().y + collBox.getGlobalBounds().height / 2 > destPoint.getPosition().y) {
		dir.y = -speed;
	}
	else if (collBox.getPosition().y + collBox.getGlobalBounds().height / 2 < destPoint.getPosition().y) {
		dir.y = speed;
	}
	else {
		dir.y = 0;
	}
	bot_shape.move(dir);
	collBox.setPosition(bot_shape.getPosition().x, bot_shape.getPosition().y + bot_shape.getGlobalBounds().height / 2);

}

void Bot::render(sf::RenderTarget& target)
{
	target.draw(bot_shape);
}

void Bot::reset()
{
	dir = sf::Vector2f{ 0, 0 };
	bot_shape.setPosition(880, 300);
	collBox.setPosition(bot_shape.getPosition().x, bot_shape.getPosition().y + bot_shape.getGlobalBounds().height / 2);

}

sf::FloatRect Bot::getFRect() const
{
	return bot_shape.getGlobalBounds();
}

sf::FloatRect Bot::getColliderRect() const
{
	return collBox.getGlobalBounds();
}
