#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 7.f;
	this->hpMax = 10;
	this->hp = this->hpMax;
}

void Player::intiShape()
{
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(70.f, 70.f));
}

//void Player::initTexture()
//{
//	if (this->hp <= 15)
//	{
//		sf::Texture texture;
//		texture.loadFromFile("D:/MyFirstGame/FirstGame/FirstGame/Texturetdam.jpg");
//		this->shape.setTexture(&texture);
//	}
//	if (this->hp >= 16 && this->hp <= 30)
//	{
//		sf::Texture texture;
//		texture.loadFromFile("Texture/avtbb.jpg");
//		this->shape.setTexture(&texture);
//	}
//	if (this->hp > 30 && this->hp <= 60)
//	{
//		sf::Texture texture;
//		texture.loadFromFile("Texture/avt.jpg");
//		this->shape.setTexture(&texture);
//	}
//	if (this->hp > 60)
//	{
//		sf::Texture texture;
//		texture.loadFromFile("Texture/backzoom.jpg");
//		this->shape.setTexture(&texture);
//	}
//}

// Constructot n Destructor
Player::Player(float x, float y)
{
	this->shape.setPosition(x, y);
	this->initVariables();
	this->intiShape();
	this->initTexture();
}

Player::~Player()
{

}

void Player::updateInput()
{
	//Keyboard Input
	
	// Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->shape.move(-this->movementSpeed, 0.f);
	}
	//Right
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->shape.move(this->movementSpeed, 0.f);
	}
	//Down
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->shape.move(0.f, -this->movementSpeed);
	}
	//Up
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->shape.move(0.f, this->movementSpeed);
	}
}

const sf::RectangleShape& Player::getShape() const
{
	return this->shape;
}

void Player::updateWindowBoundCollision(const sf::RenderTarget *target)
{
	if (this->shape.getGlobalBounds().left <= 0.f)
	{
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	}
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
	{
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	}
	if (this->shape.getGlobalBounds().top <= 0.f)
	{
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	}
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
	{
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
	}
}

void Player::update(const sf::RenderTarget* target)
{
	
	//Update input
	this->updateInput();
	//Window bounds collision
	this->updateWindowBoundCollision(target);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::takeDamage(const int damage)
{
	if (this->hp > 0)
		this->hp -= damage;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::gainHealing(const int health)
{
	if (this->hp < this->hpMax)
		this->hp += health;
	if (this->hp > this->hpMax)
		this->hp = this->hpMax;
}


