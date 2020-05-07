#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball {
private:
	Vector2f mPosition;
	RectangleShape mShape;
	float mSpeed = 1000.f;
	float mDirectionX = .2f;
	float mDirectionY = .2f;

public:
	Ball(float startX, float startY);
	FloatRect getPosition() const;
	RectangleShape getShape() const;
	float getXVelocity();
	float getYVelocity();
	
	void reboundSides();
	void reboundBatOrTop();
	void reboundBottom();
	void hitTop(float x, float y);
	void update(Time dt);

};