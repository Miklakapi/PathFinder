#include "Square.hpp"

Square::Square() : RectangleShape(){
	setSize(Vector2f{ 20,20 });
	reset();
}

void Square::setType(Type type) {
	this->type = type;
	switch (type) {
	case Path:
		setFillColor(Color{ 64,64,64 });
		break;
	case Road:
		setFillColor(Color::Green);
		break;
	case Direction:
		if (type == Type::Path)setFillColor(Color{ 64, 64, 64 });
		else if (type == Type::Road) setFillColor(Color::Green);
		break;
	case CorrectWay:
		setFillColor(Color::Blue);
		break;
	case Wall:
		setFillColor(Color::Black);
		break;
	case Start:
		setFillColor(Color::Red);
		break;
	case Stop:
		setFillColor(Color::Red);
		break;
	}
}

Type Square::getType() {
	return type;
}

void Square::setToStart(Square* startNode) {
	A = abs(startNode->getPosition().x - getPosition().x) + abs(startNode->getPosition().y - getPosition().y);
	A /= 20;
	sum = A + B;
}

void Square::setToStart(int number) {
	A = number;
	sum = A + B;
}

void Square::setToEnd(Square* endNode) {
	B = abs(endNode->getPosition().x - getPosition().x) + abs(endNode->getPosition().y - getPosition().y);
	B /= 20;
	sum = A + B;
}

int Square::getToStart() {
	return A;
}

int Square::getToEnd() {
	return B;
}

int Square::getSum() {
	return sum;
}

void Square::setParent(int parent) {
	this->parent = parent;
}

int Square::getParent() {
	return parent;
}

void Square::reset() {
	A = 0;
	B = 0;
	sum = 0;
	setType(Type::Path);
	parent = 0;
}