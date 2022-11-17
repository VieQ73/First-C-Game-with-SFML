#pragma once
#include"Ball.h"

class Player
{
private:
	sf::RectangleShape shape;
	float movementSpeed;

	int hp;
	int hpMax;


	void initVariables();
	void intiShape();
	//void initTexture();

public:
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();

	//Accessors
	const int& getHp() const;
	const int& getHpMax() const;

	const sf::RectangleShape& getShape() const;

	void updateTexture();
	void takeDamage(const int damage);
	void gainHealing(const int health);
	void updateInput();
	void updateWindowBoundCollision(const sf::RenderTarget * target);

	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

