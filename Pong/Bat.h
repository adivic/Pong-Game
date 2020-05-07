#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"

using namespace sf;

class Bat {
private:
	Vector2f mPosition;
	RectangleShape mShape;
	float mSpeed = 1000.f;
	bool bMoveLeft = false;
	bool bMoveRight = false;

public:
	Bat(float startX, float startY);
	FloatRect getPosition();
	RectangleShape getShape();
	void moveLeft();
	void moveRight();
	void stopRight();
	void stopLeft();
	void update(Time dt);

	void setAiBatSpeed(float speed);

	void aiMovement(Ball& ball, RenderWindow& window, Time dt);
};