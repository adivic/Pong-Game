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
	if (ball.getShape().getPosition().x < 0 || ball.getShape().getPosition().x + ball.getShape().getRadius() > window.getSize().x) {
		ball.reboundSides();
	}
	
	if (ball.getShape().getPosition().y > window.getSize().y) {
		ball.reboundBottom(window);
		mAiScore++;
	}

	if (isOverlappinig(ball.getShape(), aiBat.getPosition())) {
		ball.reboundBatOrTop();
	}

	//hits top
	if (ball.getShape().getPosition().y < 0) {
		ball.hitTop(window.getSize().x/2, window.getSize().y/2);
		mScore++;
	}

	if (isOverlappinig(ball.getShape(), bat.getPosition())) {
		ball.reboundBatOrTop();
	}
}

bool Game::isOverlappinig(CircleShape circle, FloatRect rect) {
	float distanceX = abs(circle.getPosition().x - rect.left);
	float distanceY = abs(circle.getPosition().y - rect.top);

	if (distanceX > (rect.width / 2 + circle.getRadius())) return false;
	if (distanceY > (rect.height / 2 + circle.getRadius())) return false;

	if (distanceX <= (rect.width / 2 + circle.getRadius())) return true;
	if (distanceY <= (rect.height / 2 + circle.getRadius())) return false;
}

void Game::checkGameEnd() {
	if (mScore == 5 || mAiScore == 5) {
		mScore = 0;
		mAiScore = 0;
	}
}

