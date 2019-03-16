#include "Play.hpp"

Play::Play(string file){
	map.loadLv(file);
	bot = new PathFinder(&map);
}

Play::Type Play::run() {
	if (Keyboard::isKeyPressed(Keyboard::Space) && clock.getElapsedTime().asSeconds() >= 0.2) {
		clock.restart();
		on = !on;
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape)) return Type::Return;
	if (Keyboard::isKeyPressed(Keyboard::R) && clock.getElapsedTime().asSeconds() >= 0.2) {
		clock.restart();
		reset();
	}
	if (on) bot->run();
	return Type::None;
}

void Play::draw(RenderWindow& window) {
	map.draw(window);
}

void Play::reset() {
	map.reset();
	bot->reset();
}

Play::~Play() {
	delete bot;
}