#pragma once
#include"Player.h"
#include"Ball.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;
	//player
	Player player;
	float points;

	//Text & font
	sf::Font font;
	sf::Text guiText;
	

	//Ball
	std::vector<Ball> balls;
	float spawnTimermax;
	float spawnTimer;
	int maxBalls;

	//Functions
	void initVariables();
	void initWindow();
	void initFont();
	void initText();

public:
	//Constructors n Destructors
	Game();

	~Game();
	//Accessors

	//Modifiers

	//Functions
	const bool running() const;

	void pollEvents();

	void spawnBalls();
	void updateCollision();

	void updateGui();
	void renderGui(sf::RenderTarget* target);

	void update();
	void render();

};

