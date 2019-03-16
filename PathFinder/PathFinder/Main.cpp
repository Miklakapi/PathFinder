#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "Game.hpp"

using namespace sf;

int main() {
	RenderWindow app{ VideoMode{1280,720,32}, "Path Finder", Style::Close };
	app.setFramerateLimit(60);

	Game game(app);

	while (app.isOpen()) {

		Event event;
		while (app.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				app.close();
				break;
			}
		}

		game.run(app);

		app.clear();
		game.draw(app);
		app.display();
	}
}