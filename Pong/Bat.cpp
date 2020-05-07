#include "Bat.h"
#include <cmath>

Bat::Bat(float startX, float startY) {
	mPosition.x = startX;
	mPosition.y = startY;

	mShape.setSize(sf::Vector2f(50, 5)); //TODO remove magic number
	mShape.setPosition(mPosition);
}

FloatRect Bat::getPosition() {
	return mShape.getGlobalBounds();
}

RectangleShape Bat::getShape() {
	return mShape;
}

void Bat::moveLeft() {
	bMoveLeft = true;
}

void Bat::moveRight() {
	bMoveRight = true;
}

void Bat::stopLeft() {
	bMoveLeft = false;
}

void Bat::stopRight() {
	bMoveRight = false;
}

void Bat::update(Time dt) {
	if (bMoveLeft) {
		mPosition.x -= mSpeed * dt.asSeconds();
	}
	if (bMoveRight) {
		mPosition.x += mSpeed * dt.asSeconds();
	}
	mShape.setPosition(mPosition);
}

void Bat::aiMovement(Ball& ball, RenderWindow& window, Time dt) {
	
	if (ball.getPosition().top < window.getSize().y /2 ) {
		

		if (ball.getPosition().left < getPosition().left && (getPosition().left) >= 0) {
			moveLeft();
		} else {
			stopLeft();
		}
		if (ball.getPosition().left > getPosition().left  && (getPosition().left) <= window.getSize().x - getPosition().width) {
			moveRight();
		} else {
			stopRight();
		}
	} else {
		if (getPosition().left < window.getSize().x / 2 - getPosition().width) {
			moveRight();
		} else {
			stopRight();
		}
		if (getPosition().left > window.getSize().x / 2 - getPosition().width) {
			moveLeft();
		} else {
			stopLeft();
		}
	}
	update(dt);
}

void Bat::setAiBatSpeed(float speed) {
	mSpeed = speed;
}