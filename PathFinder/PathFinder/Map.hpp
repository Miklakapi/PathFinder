#pragma once
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include <fstream>
#include "Square.hpp"

using namespace sf;
using namespace std;

class Map{

	friend class PathFinder;
	
	Square* square;

	string fileName;

public:

	Map();
	
	void loadLv(string file = "LV1.txt");

	void draw(RenderWindow& window);

	void reset();

	~Map();
};

