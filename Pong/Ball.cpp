#include "Ball.h"

Ball::Ball(float startX, float startY) {
	mPosition.x = startX;
	mPosition.y = startY;
	mShape.setSize(sf::Vector2f(10,10));
	mShape.setPosition(mPosition);
}

FloatRect Ball::getPosition() const {
	return mShape.getGlobalBounds();
}

RectangleShape Ball::getShape() const {
	return mShape;
}

float Ball::getXVelocity() {
	return mDirectionX;
}

float Ball::getYVelocity() {
	return mDirectionY;
}

void Ball::reboundSides() {
	mDirectionX = -mDirectionX;
}

void Ball::reboundBatOrTop() {
	mDirectionY = -mDirectionY;
}

void Ball::reboundBottom(RenderWindow& window) {
	mPosition.y = window.getSize().y/2;
	mPosition.x = window.getSize().x /2;
	mDirectionY = -mDirectionY;
}

void Ball::update(Time dt) {
	mPosition.y += mDirectionY * mSpeed * dt.asSeconds();
	mPosition.x += mDirectionX * mSpeed * dt.asSeconds();
	mShape.setPosition(mPosition);
}

void Ball::hitTop(float x, float y) {
	mPosition.x = x;
	mPosition.y = y;
	mDirectionY = -mDirectionY;
	mShape.setPosition(mPosition);
}