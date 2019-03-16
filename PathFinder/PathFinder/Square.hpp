#pragma once
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <math.h>

using namespace sf;

enum Type {
	Path,
	Road,
	Direction,
	CorrectWay,
	Wall,
	Start,
	Stop
};

class Square : public RectangleShape {

	Type type;

	int parent;

	//Distances
	int A; // to start node

	int B; //to end node

	int sum; // A + B

public:

	Square();

	void setType(Type type);

	Type getType();

	void setToStart(Square* startNode);

	void setToStart(int number);

	void setToEnd(Square* endNode);

	int getToStart();

	int getToEnd();

	int getSum();

	void setParent(int parent);

	int getParent();

	void reset();
};

