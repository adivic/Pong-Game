
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
	batAi.setAiBatSpeed(300.f);

	Ball ball(game->getScreenResolution().x / 2, 50);



	Clock clock;
	Text hud;
	Font font;
	font.loadFromFile("F:/C++ Projects/Pong/fonts/advanced_dot_digital-7.ttf");
	hud.setFont(font);
	hud.setCharacterSize(25);
	hud.setFillColor(sf::Color::White);
	hud.setPosition(20, 20);
	// Find better position for this
	std::stringstream ss;
	ss << "Score: " << game->getScore();// << " Lives: " << game->getLives();
	hud.setString(ss.str());
	
	while (window.isOpen()) {
		//Hnadle player input
		game->handlePlayerInput(window, bat);
		
		//update bat, ball and hud
		Time dt = clock.restart();
		bat.update(dt);
		ball.update(dt);	
		batAi.aiMovement(ball, window, dt);

		game->checkCollision(window,ball, bat, batAi);

		//draw everything
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(batAi.getShape());
		window.draw(ball.getShape());
		window.display();

	}

	return 0;
}
