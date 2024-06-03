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

void Game::updateDestPos()
{
	
	if (gameBall.getDir().y < 0) {
		endPoint.setPosition(sf::Vector2f{ shapes[0].getPosition().x + shapes[0].getGlobalBounds().width,
	shapes[0].getPosition().y - shapes[0].getGlobalBounds().height});
	}
	else {
		endPoint.setPosition(sf::Vector2f{ shapes[0].getPosition().x + shapes[0].getGlobalBounds().width,
	shapes[0].getPosition().y + shapes[0].getGlobalBounds().height});
	}
	
	updateDest = false;
}

void Game::updateText()
{
	std::stringstream ss;
	ss << std::to_string(pScore);
	playerScoreText.setString(ss.str());

	std::ostringstream ss2;
	ss2 << std::to_string(eScore);
	enemyScoreText.setString(ss2.str());

}

void Game::drawPlayerLine()
{
	//if ball hits upper of down borders of game field or hits player
	if (updatePlayersBallCollision()) {
		botsTurn = true;
		gameBall.updateDir();
		if (shapes.size() != 0) {
			shapes.pop_back();
		}
		sf::RectangleShape line{ sf::Vector2f(890.f, 3.f) };
		line.setPosition(0, gameBall.getPos().y);
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
	updateDest = true;

	players.push_back(GamePlayer);

	endPoint.setRadius(5.f);
	endPoint.setFillColor(sf::Color::Red);

	pScore = 0;
	eScore = 0;


}

void Game::initWindow()
{
	GameWindow = std::make_shared<sf::RenderWindow>(vidMode, "PinPong", sf::Style::Titlebar | sf::Style::Close);

	//set frame limit to 60
	GameWindow->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!mainFont.loadFromFile("pingpong.regular.ttf")) {
		std::clog << "ERROR::CANTLOADFONT::pingpong\n";
	}

}

void Game::initTexts()
{
	playerScoreText.setFont(mainFont);
	playerScoreText.setCharacterSize(24);
	playerScoreText.setPosition(10.f, 10.f);

	enemyScoreText.setFont(mainFont);
	enemyScoreText.setCharacterSize(24);
	enemyScoreText.setPosition(880.f, 10.f);

	//set text to Text
	std::stringstream ss;
	ss << std::to_string(pScore);
	playerScoreText.setString(ss.str());
	

	std::stringstream ss2;
	ss2 << std::to_string(eScore);
	enemyScoreText.setString(ss2.str());

}

void Game::checkSidesCollision()
{
	if (gameBall.getPos().x > 900) {
		pScore++;
		std::cout << "Man score\n";
		restartGame();
	}
	else if (gameBall.getPos().x < 0) {
		eScore++;
		std::cout << "Bot score\n";
		restartGame();
	}
	

}

void Game::restartGame()
{
	GamePlayer->reset();

	gameBall.reset();

	bot1->reset();

	botsTurn = false;
	updateDest = true;

	updateText();
}

//public scope

Game::Game()
{
	initVars();
	initWindow();

	initFonts();
	initTexts();
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
	
		//if ball goes up
		if (updateDest) {
			updateDestPos();
		}
			
		
		bot1->update(endPoint);
		if (updateBotCollsion()) {
			gameBall.updateDir();
			botsTurn = false;
			updateDest = true;
			shapes.pop_back();
		}
		
	}

	gameBall.update();

	checkSidesCollision();

	//chekc top down collision
	if (gameBall.checkTopDownCollision()) {
		botsTurn = true;
		
		//bot goes down after rebound of border
		if (gameBall.getDir().y > 0) {
			if (gameBall.getPos().x < 450) {
				endPoint.setPosition(sf::Vector2f{ bot1->getFRect().getPosition().x, bot1->getFRect().getPosition().y + bot1->getFRect().height * 2 });
			}
			else if (gameBall.getPos().x > 500) {
				endPoint.setPosition(sf::Vector2f{ bot1->getFRect().getPosition().x, bot1->getFRect().getPosition().y + bot1->getFRect().height / 2});
			}
			else {
				endPoint.setPosition(sf::Vector2f{ bot1->getFRect().getPosition().x, bot1->getFRect().getPosition().y + bot1->getFRect().height });
			}
		}
		else {
			if (gameBall.getPos().x < 450) {
				endPoint.setPosition(sf::Vector2f{ bot1->getFRect().getPosition().x, bot1->getFRect().getPosition().y - bot1->getFRect().height * 2 });
			}
			else if (gameBall.getPos().x > 500) {
				endPoint.setPosition(sf::Vector2f{ bot1->getFRect().getPosition().x, bot1->getFRect().getPosition().y + bot1->getFRect().height / 2 });
			}
			else {
				endPoint.setPosition(sf::Vector2f{ bot1->getFRect().getPosition().x, bot1->getFRect().getPosition().y - bot1->getFRect().height });
			}
		}

	}

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

	gameBall.render(*GameWindow);

	GameWindow->draw(playerScoreText);
	GameWindow->draw(enemyScoreText);

	GameWindow->display();
}
