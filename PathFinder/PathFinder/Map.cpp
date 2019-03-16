#include "Map.hpp"

Map::Map(){
	square = new Square[2304];
	fileName = "LV1.txt";
	int n(0);
	for (int y = 0; y < 36; y++) {
		for (int x = 0; x < 64; x++) {
			(square + n)->setPosition(Vector2f{ float(20 * x),float(20 * y) });
			n++;
		}
	}
}

void Map::loadLv(string file) {
	fileName = file;
	fstream stream;
	(stream.open(file, ios::in));
	if (!stream.is_open()) {
		exit(0);
	}
	int k = 0;
	for (int i = 0; i < 36; i++) {
		string line;
		getline(stream, line);
		for (int j = 0; j < 64; j++) {
			switch (line.at(j)) {
			case '#':
				(square + k)->setType(Type::Wall);
				break;
			case '-':
				(square + k)->setType(Type::Path);
				break;
			case 'S':
				(square + k)->setType(Type::Start);
				break;
			case 'E':
				(square + k)->setType(Type::Stop);
				break;
			}
			k++;
		}
	}
	stream.close();
}

void Map::draw(RenderWindow& window) {
	for (int i = 0; i < 2304; i++) {
		window.draw(*(square + i));
	}
}

void Map::reset() {
	for (int i = 0; i < 2304; i++) (square + i)->reset();
	loadLv(fileName);
}

Map::~Map(){
	delete[] square;
}
