#pragma once
#include<iostream>
#include<ctime>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

enum BallTypes { DEFAULT = 0, Damaging, Healing, Nroftypes };

class Ball
{
private:
	sf::CircleShape shape;
	int type;

	void initShape(const sf::RenderWindow& window);
public:
	Ball(const sf::RenderWindow& window, int type);
	virtual ~Ball();

	//Accessors
	const int& getType() const;
	
	const sf::CircleShape& getShape() const;

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

