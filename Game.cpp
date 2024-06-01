#include "stdafx.h"

#include "Game.h"

//private scope

void Game::updateEvents()
{
	while (GameWindow->pollEvent(windowEvents)) {
		switch (windowEvents.type)
		{
		case sf::Event::Closed:
			GameWindow->close();
			windowOpen = false;
			break;
		default:
			break;
		}
	}
}

bool Game::updatePlayersBallCollision()
{
	for (auto& i : players) {
		if (gameBall.checkCollisionPlayer(i->getFRect())) {
			return true;
		}
	}
	return false;
}

bool Game::updateBotCollsion()
{
	if (gameBall.checkCollisionPlayer(bot1->getFRect())) {
		return true;
	}
	return false;
}

void Game::drawPlayerLine()
{
	if (updatePlayersBallCollision()) {
		botsTurn = true;
		gameBall.updateDir();
		if (shapes.size() != 0) {
			shapes.pop_back();
		}
		sf::RectangleShape line{ sf::Vector2f(800.f, 3.f) };
		line.setPosition(gameBall.getPos().x + 25, gameBall.getPos().y);
		auto angle = atan(abs(gameBall.getDir().y) / gameBall.getDir().x) * 180 / 3.14;
		if (gameBall.getDir().y < 0) {
			line.setRotation(-angle);
		}
		else {
			line.setRotation(angle);
		}
		shapes.push_back(line);
	}
}

void Game::initVars()
{
	GameWindow = nullptr;

	//setup window video mode 900x600
	vidMode.width = 900;
	vidMode.height = 600;

	windowOpen = true;

	GamePlayer = std::make_shared<Player>(sf::Vector2f{ 10, 300 }, sf::Keyboard::W, sf::Keyboard::S);
	GamePlayer2 = nullptr;
	bot1 = std::make_shared<Bot>();

	botsTurn = false;

	players.push_back(GamePlayer);

	test = std::make_shared<sf::CircleShape>(2.5f);
	test->setRadius(5.f);
	test->setFillColor(sf::Color::Red);


}

void Game::initWindow()
{
	GameWindow = std::make_shared<sf::RenderWindow>(vidMode, "PinPong", sf::Style::Titlebar | sf::Style::Close);

	//set frame limit to 60
	GameWindow->setFramerateLimit(60);
}

//public scope

Game::Game()
{
	initVars();
	initWindow();
}

bool Game::isOpen() const
{
	return windowOpen;
}

void Game::update()
{

	updateEvents();

	GamePlayer->update();
	drawPlayerLine();
	//if playing vs bot player2 doesn't exist 
	if (GamePlayer2 != nullptr) {
		GamePlayer2->update();
	}
	if (bot1 != nullptr && shapes.size() != 0 && botsTurn) {
	

		if (gameBall.getDir().y < 0) {
			test.setPosition(shapes[0].getPosition().x + shapes[0].getGlobalBounds().width + 70, shapes[0].getPosition().y -
				shapes[0].getGlobalBounds().height - (bot1->getFRect().height / 2) * (1 + gameBall.getDir().y));
		}
		else {
			test.setPosition(shapes[0].getPosition().x + shapes[0].getGlobalBounds().width + 70, shapes[0].getPosition().y +
				shapes[0].getGlobalBounds().height + (bot1->getFRect().height / 2) * (1+gameBall.getDir().y));
		}
		
		bot1->update(test);
		if (updateBotCollsion()) {
			gameBall.updateDir();
			botsTurn = false;
			shapes.pop_back();
		}
		
	}

	gameBall.update();

}

void Game::render()
{
	GameWindow->clear();

	GamePlayer->render(*GameWindow);
	if (GamePlayer2 != nullptr) {
		GamePlayer2->render(*GameWindow);
	}
	if (bot1 != nullptr) {
		bot1->render(*GameWindow);
	}
	
	for (auto& i : shapes) {
		GameWindow->draw(i);
	}

	gameBall.render(*GameWindow);

	GameWindow->draw(test);

	GameWindow->display();
}
