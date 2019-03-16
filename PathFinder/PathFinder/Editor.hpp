#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <string>
#include "Map.hpp"
#include "PathFinder.hpp"

using namespace sf;
using namespace std;

class Editor{

public:

	enum Type {
		None,
		Return
	};

private:

	Square* square;

	Map* map;

	PathFinder* bot;

	bool isStart;

	bool isEnd;

	bool exist;

	bool start;

	Clock clock;

public:

	Editor();

	Type run(RenderWindow& window);

	void draw(RenderWindow& window);

	void clear();
	
	~Editor();
};

