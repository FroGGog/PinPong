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
	std::vector<sf::Text> allText;

	sf::CircleShape endPoint;

	Ball gameBall;

	//text stuff
	sf::Font mainFont;
	sf::Text playerScoreText;
	sf::Text enemyScoreText;

	bool botsTurn;
	bool updateDest;

	short pScore, eScore;

	void updateEvents();

	//check if ball collides with any player
	bool updatePlayersBallCollision();
	bool updateBotCollsion();

	void updateDestPos();

	void updateText();

	void drawPlayerLine();
	//init stuff
	void initVars();
	void initWindow();

	void initFonts();
	void initTexts();

	void checkSidesCollision();

	void restartGame();

public:

	Game();


	//getters
	bool isOpen() const;

	void update();

	void render();



};

