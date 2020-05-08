
#include "Bat.h"
#include "Ball.h"
#include "Game.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
	Game *game = new Game(Vector2i(800,600));
	// TODO Remove magic number
	VideoMode vm(game->getScreenResolution().x, game->getScreenResolution().y);

	RenderWindow window(vm, "Pong", Style::Resize);
	


	Bat bat(game->getScreenResolution().x / 2, game->getScreenResolution().y - 20);
	Bat batAi(game->getScreenResolution().x / 2, 20);
	batAi.setAiBatSpeed(280.f);

	Ball ball(game->getScreenResolution().x / 2, 50);



	Clock clock;
	Text hud;
	Font font;
	font.loadFromFile("F:/C++ Projects/Pong/fonts/advanced_dot_digital-7.ttf");
	hud.setFont(font);
	hud.setCharacterSize(25);
	hud.setFillColor(sf::Color::White);
	hud.setPosition(20, window.getSize().y - 40);
	Text aiHud;
	aiHud.setFont(font);
	aiHud.setCharacterSize(25);
	aiHud.setFillColor(sf::Color::White);
	aiHud.setPosition(20, 20);

	while (window.isOpen()) {
		//Hnadle player input
		game->handlePlayerInput(window, bat);
		
		//update bat, ball and hud
		Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);	
		batAi.aiMovement(ball, window, dt);

		game->checkCollision(window,ball, bat, batAi);

		// Find better position for this
		std::stringstream ss;
		std::stringstream ssAi;
		ss << "Score: " << game->getScore();
		hud.setString(ss.str());
		ssAi << "AI: " << game->getAiScore();
		aiHud.setString(ssAi.str());


		//draw everything
		window.clear();
		window.draw(hud);
		window.draw(aiHud);
		window.draw(bat.getShape());
		window.draw(batAi.getShape());
		window.draw(ball.getShape());
		window.display();

	}

	return 0;
}
