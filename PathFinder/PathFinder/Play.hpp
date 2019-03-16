#pragma once
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "Map.hpp"
#include "PathFinder.hpp"

using namespace sf;
using namespace std;

class Play{

public:

	enum Type {
		None,
		Return
	};

private:

	Map map;

	PathFinder* bot;

	bool on;

	Clock clock;

public:

	Play(string file = "Lv1.txt");
	
	Type run();

	void draw(RenderWindow& window);

	void reset();

	~Play();
};

