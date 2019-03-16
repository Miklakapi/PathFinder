#include "Editor.hpp"

Editor::Editor(){
	square = new Square[2304];
	clear();
	int i = 0;
	for (int y = 0; y < 36; y++) {
		for (int x = 0; x < 64; x++) {
			(square + i)->setPosition({ float(x * 20),float(y * 20) });
			i++;
		}
	}
}

Editor::Type Editor::run(RenderWindow& window) {
	if (!exist) {
		if (Keyboard::isKeyPressed(Keyboard::Enter) && isEnd && isStart && clock.getElapsedTime().asSeconds() >= 0.2) {
			exist = true;

			fstream stream;
			stream.open("EDITOR.txt", ios::out);
			for (int i = 0; i < 2304; i++) {
				string ch;
				if ((square + i)->getType() == ::Type::Wall) ch = "#";
				else if ((square + i)->getType() == ::Type::Path) ch = "-";
				else if ((square + i)->getType() == ::Type::Start) ch = "S";
				else if ((square + i)->getType() == ::Type::Stop) ch = "E";
				stream << ch;
				if ((i + 1) % 64 == 0) stream << endl;
			}
			stream.close();

			map = new Map;
			map->loadLv("EDITOR.txt");
			bot = new PathFinder(map);

			clock.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::R) && clock.getElapsedTime().asSeconds() >= 0.2) {
			clear();
			clock.restart();
		}
		if (Mouse::isButtonPressed(Mouse::Left)) {
			Vector2i pos = { int(Mouse::getPosition(window).x), int(Mouse::getPosition(window).y) };

			int number = int(int(pos.x / 20)) + int(int((pos.y) / 20) * 64);

			(square + number)->setType(::Type::Wall);
		}
		else if (Mouse::isButtonPressed(Mouse::Right)) {
			Vector2i pos = { int(Mouse::getPosition(window).x), int(Mouse::getPosition(window).y) };

			int number = int(int(pos.x / 20)) + int(int((pos.y) / 20) * 64);

			if (!(number >= 0 && number <= 63 || number >= 2240 && number <= 2303 || number % 64 == 0 || (number + 1) % 64 == 0)) {
				if ((square + number)->getType() == ::Type::Start) isStart = false;
				else if ((square + number)->getType() == ::Type::Stop) isEnd = false;
				(square + number)->setType(::Type::Path);
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::S) && !isStart) {
			Vector2i pos = { int(Mouse::getPosition(window).x), int(Mouse::getPosition(window).y) };

			int number = int(int(pos.x / 20)) + int(int((pos.y) / 20) * 64);

			if (!(number >= 0 && number <= 63 || number >= 2240 && number <= 2303 || number % 64 == 0 || (number + 1) % 64 == 0)) {
				if ((square + number)->getType() == ::Type::Stop) isEnd = false;
				(square + number)->setType(::Type::Start);
				isStart = true;
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::E) && !isEnd) {
			Vector2i pos = { int(Mouse::getPosition(window).x), int(Mouse::getPosition(window).y) };

			int number = int(int(pos.x / 20)) + int(int((pos.y) / 20) * 64);

			if (!(number >= 0 && number <= 63 || number >= 2240 && number <= 2303 || number % 64 == 0 || (number + 1) % 64 == 0)) {
				if ((square + number)->getType() == ::Type::Start) isStart = false;
				(square + number)->setType(::Type::Stop);
				isEnd = true;
			}
		}
	}
	else {
		if (Keyboard::isKeyPressed(Keyboard::Enter) && clock.getElapsedTime().asSeconds() >= 0.2) {
			exist = false;
			start = false;

			delete map;
			delete bot;

			clock.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Space) && clock.getElapsedTime().asSeconds() >= 0.2) {
			start = !start;
			clock.restart();
		}
		else if (Keyboard::isKeyPressed(Keyboard::R) && clock.getElapsedTime().asSeconds() >= 0.2) {
			map->reset();
			bot->reset();
		}

		if(start) bot->run();
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape) && clock.getElapsedTime().asSeconds() >= 0.2) {
		return Type::Return;
	}
	return Type::None;
}

void Editor::draw(RenderWindow& window) {
	if(exist) map->draw(window);
	else {
		for (int i = 0; i < 2304; i++) {
			window.draw(*(square + i));
		}
	}
}

void Editor::clear() {
	isStart = false;
	isEnd = false;
	exist = false;
	start = false;
	for (int i = 0; i < 2304; i++) {
		(square + i)->reset();
		if (i >= 0 && i <= 63) (square + i)->setType(::Type::Wall);
		else if (i >= 2240 && i <= 2303) (square + i)->setType(::Type::Wall);
		else if (i % 64 == 0) (square + i)->setType(::Type::Wall);
		else if ((i + 1) % 64 == 0) (square + i)->setType(::Type::Wall);
	}
}

Editor::~Editor(){
	delete [] square;
	if (exist) {
		delete bot;
		delete map;
	}
}