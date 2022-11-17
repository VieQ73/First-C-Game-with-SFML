#include "Game.h"
#include<sstream>

void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimermax = 10.f;
	this->spawnTimer = this->spawnTimermax;
	this->maxBalls = 10;
	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "First Game", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);

}

void Game::initFont()
{
	this->font.loadFromFile("Fonts/MTO CHANEY.TTF");
}

void Game::initText()
{
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::Black);
	this->guiText.setOutlineThickness(2.f);
	this->guiText.setOutlineColor(sf::Color::White);
	this->guiText.setCharacterSize(36);
	this->guiText.setStyle( sf::Text::Underlined);
}


//Constructors n Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

//Functions

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
		}
	}
}

void Game::spawnBalls()
{
	//Timer
	if (this->spawnTimer < this->spawnTimermax)
		this->spawnTimer += 1.f;
	else
	{
		if (this->balls.size() < this->maxBalls)
		{
			this->balls.push_back(Ball(*this->window, rand() % BallTypes :: Nroftypes));
			this->spawnTimer = 0.f;
		}
	}
}


void Game::updateCollision()
{
	// Check the collision
	for (size_t i = 0; i < this->balls.size(); i++)
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->balls[i].getShape().getGlobalBounds()))
		{
			switch (this->balls[i].getType())
			{
			case BallTypes::DEFAULT:
				this->points++;
				break;
			case BallTypes::Damaging:
				this->player.takeDamage(1);
				break;
			case BallTypes::Healing:
				this->player.gainHealing(1);
				this->points += 0.5f;
				break;
			}
			this->balls.erase(this->balls.begin() + i);
		}
	}
}


void Game::updateGui()
{
	std::stringstream ss;

	ss << "POINTS:" << this->points << "\n"
		<< "HEALTH:" << this->player.getHp() << "/" << this->player.getHpMax() << "\n";
	this->guiText.setString(ss.str());
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::update()
{
	this->pollEvents();

	this->spawnBalls();

	this->updateCollision();

	this->updateGui();

	this->player.update(this->window);
}

void Game::render()
{
	this->window->clear();

	//Render stuff
	this->player.render(this->window);

	for (auto i : this->balls)
	{
		i.render(*this->window);
	}

	//Render Gui
	this->renderGui(this->window);

	this->window->display();
}
