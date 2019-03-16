#pragma once
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "Map.hpp"

using namespace sf;

class PathFinder {

	Map* map;

	int startNode;

	int endNode;

	bool start;

	bool stop;

	int length;
	int lengthCopy;

	int* road;

	Clock clock;

	int checkMove(int move, int newMove);

	void makeMove(int move);

public:

	PathFinder(Map* map);

	void run();

	void reset();

	~PathFinder();
};