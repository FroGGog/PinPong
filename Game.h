#pragma once
#include "Player.h"
#include "Ball.h"
#include "Bot.h"

class Game
{
private:


	//screen vars
	sf::VideoMode vidMode;
	std::shared_ptr<sf::RenderWindow> GameWindow;
	bool windowOpen;

	sf::Event windowEvents;

	//gameplay stuff
	std::shared_ptr<Player> GamePlayer;
	std::shared_ptr<Player> GamePlayer2;
	std::shared_ptr<Bot> bot1;

	std::vector<std::shared_ptr<Player>> players;
	std::vector<sf::RectangleShape> shapes;

	sf::CircleShape test;

	Ball gameBall;

	bool botsTurn;
	bool updateDest;

	void updateEvents();

	//check if ball collides with any player
	bool updatePlayersBallCollision();
	bool updateBotCollsion();

	void updateDestPos();

	void drawPlayerLine();
	//init stuff
	void initVars();
	void initWindow();

	void checkSidesCollision();

	void restartGame();

public:

	Game();


	//getters
	bool isOpen() const;

	void update();

	void render();



};

