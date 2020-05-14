#include "Game.h"
#include <sstream>

Game::Game() {
	mScreenResolution.x = VideoMode::getDesktopMode().width;
	mScreenResolution.y = VideoMode::getDesktopMode().height;
	mWindow.create(sf::VideoMode(800,600), "Pong", Style::Resize);
	mBat = new Bat(mWindow.getSize().x / 2, mWindow.getSize().y - 20);
	mAiBat = new Bat(mWindow.getSize().x / 2, 20);
	mAiBat->setAiBatSpeed(280.f);
	mBall = new Ball(mWindow.getSize().x / 2, 50);
	mScore = 0;
	mAiScore = 0;
}

void Game::update() {

	initializeHud();

	if (!bPaused) {
		//update bat, ball and hud
		mBat->update(mTime);
		mBall->update(mTime);
		mAiBat->aiMovement(*mBall, mWindow, mTime);

		checkCollision();

		setupHud();
		
	} else {
		mAiHud.setPosition(mWindow.getSize().x + 50, mWindow.getSize().y + 150);
		std::stringstream ss;
		ss << "Game Over!!\n\nPress Enter to start \n\nEsc to close game";
		mHud.setString(ss.str());
		mHud.setPosition(mWindow.getSize().x *0.3, mWindow.getSize().y *.4);

	}


}

void Game::setupHud() {
	mHud.setPosition(20, mWindow.getSize().y - 40);
	mAiHud.setPosition(20, 20);
	std::stringstream ss;
	std::stringstream ssAi;
	ss << "Score: " << mScore;
	mHud.setString(ss.str());
	ssAi << "AI: " << mAiScore;
	mAiHud.setString(ssAi.str());
}

void Game::initializeHud() {
	mFont.loadFromFile("F:/C++ Projects/Pong/fonts/advanced_dot_digital-7.ttf");
	mHud.setFont(mFont);
	mHud.setCharacterSize(25);
	mHud.setFillColor(sf::Color::White);

	mAiHud.setFont(mFont);
	mAiHud.setCharacterSize(25);
	mAiHud.setFillColor(sf::Color::White);
}

void Game::draw() {
	mWindow.clear();
	mWindow.draw(mHud);
	mWindow.draw(mAiHud);
	mWindow.draw(mBat->getShape());
	mWindow.draw(mAiBat->getShape());
	mWindow.draw(mBall->getShape());


	mWindow.display();
}

void Game::run() {
	while (mWindow.isOpen()) {
		mTime = mClock.restart();
		handleInput();
		update();
		draw();
	}
}

void Game::handleInput() {
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		if (event.type == Event::Closed)
			mWindow.close();
	}
	if (Keyboard::isKeyPressed(Keyboard::Return)) {
		if (bPaused) {
			bPaused = false;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
		mWindow.close();

	if (Keyboard::isKeyPressed(Keyboard::Left) && mBat->getPosition().left >= 0) {
		mBat->moveLeft();
	} else {
		mBat->stopLeft();
	}

	if (Keyboard::isKeyPressed(Keyboard::Right) && (mBat->getPosition().left) <= mWindow.getSize().x - mBat->getPosition().width) {
		mBat->moveRight();
	} else {
		mBat->stopRight();
	}
}

void Game::checkCollision() {
	
	//ball hits sides
	if (mBall->getShape().getPosition().x < 0 || mBall->getShape().getPosition().x + mBall->getShape().getRadius() > mWindow.getSize().x) {
		mBall->reboundSides();
	}
	
	if (mBall->getShape().getPosition().y > mWindow.getSize().y) {
		mBall->reboundBottom(mWindow);
		mAiScore++;
		checkGameEnd();
	}

	if (isOverlappinig(mBall->getShape(), mAiBat->getPosition())) {
		mBall->reboundBatOrTop();
	}

	//hits top
	if (mBall->getShape().getPosition().y < 0) {
		mBall->hitTop(mWindow.getSize().x/2, mWindow.getSize().y/2);
		mScore++;
		checkGameEnd();
	}

	if (isOverlappinig(mBall->getShape(), mBat->getPosition())) {
		mBall->reboundBatOrTop();
	}
}

bool Game::isOverlappinig(CircleShape circle, FloatRect rect) {
	float distanceX = abs(circle.getPosition().x - rect.left);
	float distanceY = abs(circle.getPosition().y - rect.top);
	
	/*if (distanceX > (rect.width / 2 + circle.getRadius())) return false;
	if (distanceY > (rect.height / 2 + circle.getRadius())) return false;

	if (distanceX <= (rect.width / 2 + circle.getRadius())) return true;
	if (distanceY <= (rect.height / 2 + circle.getRadius())) return false;*/
	return circle.getGlobalBounds().intersects(rect);
}

void Game::checkGameEnd() {
	if (mScore == GAME_SCORE || mAiScore == GAME_SCORE) {
		mScore = 0;
		mAiScore = 0;
		bPaused = true;
	}
}
