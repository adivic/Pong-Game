#include "Game.h"

Game::Game(sf::Vector2i screenResolution) {
	mScreenResolution = screenResolution;
}

sf::Vector2i Game::getScreenResolution() {
	return mScreenResolution;
}

int Game::getScore() const {
	return mScore;
}

int Game::getAiScore() const {
	return mAiScore;
}

void Game::handlePlayerInput(sf::RenderWindow& window, Bat& bat) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed)
			window.close();
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
		window.close();

	if (Keyboard::isKeyPressed(Keyboard::Left) && bat.getPosition().left >= 0) {
		bat.moveLeft();
	} else {
		bat.stopLeft();
	}

	if (Keyboard::isKeyPressed(Keyboard::Right) && (bat.getPosition().left) <= mScreenResolution.x - bat.getPosition().width) {
		bat.moveRight();
	} else {
		bat.stopRight();
	}
}

void Game::checkCollision(RenderWindow& window, Ball &ball, Bat& bat, Bat& aiBat) {
	
	//ball hits sides
	if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x) {
		ball.reboundSides();
	}
	
	if (ball.getPosition().top > window.getSize().y) {
		ball.reboundBottom(window);
		mAiScore++;
	}

	if (ball.getPosition().intersects(aiBat.getPosition())) {
		ball.reboundBatOrTop();
	}

	//hits top
	if (ball.getPosition().top < 0) {
		ball.hitTop(window.getSize().x/2, window.getSize().y/2);
		mScore++;
	}

	if (ball.getPosition().intersects(bat.getPosition())) {
		ball.reboundBatOrTop();
	}
}

void Game::checkGameEnd() {
	if (mScore == 5 || mAiScore == 5) {
		mScore = 0;
		mAiScore = 0;
	}
}

