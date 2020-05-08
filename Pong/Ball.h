#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball {
private:
	Vector2f mPosition;
	CircleShape mShape;
	float mSpeed = 1200.f;
	float mDirectionX = .2f;
	float mDirectionY = .2f;

public:
	Ball(float startX, float startY);
	CircleShape getShape() const;
	float getXVelocity();
	float getYVelocity();
	
	void reboundSides();
	void reboundBatOrTop();
	void reboundBottom(RenderWindow& window);
	void hitTop(float x, float y);
	void update(Time dt);

};