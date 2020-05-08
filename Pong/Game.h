#pragma once
#include <SFML/Graphics.hpp>
#include "Bat.h"
#include "Ball.h"

class Game {
private:
	int mScore = 0;
	int mAiScore = 0;
	sf::Vector2i mScreenResolution;

public:
	Game(sf::Vector2i screenResolution);
	
	sf::Vector2i getScreenResolution();

	int getScore() const;
	int getAiScore() const;

	void handlePlayerInput(sf::RenderWindow& window, Bat& bat);
	void checkCollision(RenderWindow& window, Ball &ball, Bat& bat, Bat&);

	void checkGameEnd();

	bool isOverlappinig(CircleShape circle, FloatRect rect);
};