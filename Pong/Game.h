#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Bat.h"

using namespace sf;

class Game {

private:
	const int GAME_SCORE = 5;
	RenderWindow mWindow;
	Clock mClock;
	Time mTime;

	Text mHud;
	Text mAiHud;
	Font mFont;

	Bat* mBat;
	Bat* mAiBat;
	Ball* mBall;
	
	int mScore;
	int mAiScore;
	Vector2i mScreenResolution;
	bool bPaused = false;

	void checkCollision();
	void checkGameEnd();
	bool isOverlappinig(CircleShape circle, FloatRect rect);
	void setupHud();
	void initializeHud();
	void handleInput();
	void update();
	void draw();

public:
	Game();
	void run();
};