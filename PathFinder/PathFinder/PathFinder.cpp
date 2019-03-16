#include "PathFinder.hpp"

PathFinder::PathFinder(Map* map) {
	this->map = map;

	start = true;
	stop = false;

	for (int i = 0; i < 2304; i++) {
		if ((map->square + i)->getType() == Type::Start) startNode = i;
		else if ((map->square + i)->getType() == Type::Stop) endNode = i;
	}
}

int PathFinder::checkMove(int move, int newMove) {
	if ((map->square + newMove)->getType() != Type::Direction) return move;
	if (move == 0) return newMove;
	if ((map->square + move)->getSum() < (map->square + newMove)->getSum()) return move;
	else if ((map->square + move)->getSum() > (map->square + newMove)->getSum()) return newMove;
	else if ((map->square + move)->getSum() == (map->square + newMove)->getSum()) {
		if ((map->square + move)->getToStart() < (map->square + newMove)->getToStart()) return move;
		else if ((map->square + move)->getToStart() > (map->square + newMove)->getToStart()) return newMove;
		else if ((map->square + move)->getToStart() == (map->square + newMove)->getToStart()) {
			if ((map->square + move)->getToEnd() < (map->square + newMove)->getToEnd()) return move;
			else if ((map->square + move)->getToEnd() < (map->square + newMove)->getToEnd()) return newMove;
			else if ((map->square + move)->getToEnd() == (map->square + newMove)->getToEnd()) return move;
		}
	}
	exit(0);
	return move;
}

void PathFinder::makeMove(int move) {
	(map->square + move)->setType(Type::Road);
	int number = (map->square + move)->getToStart();

	if ((map->square + move - 64)->getToStart() == number - 1 && (map->square + move - 64)->getType() != Type::Wall)
		(map->square + move)->setParent(move - 64);
	else if ((map->square + move + 64)->getToStart() == number - 1 && (map->square + move + 64)->getType() != Type::Wall)
		(map->square + move)->setParent(move + 64);
	else if ((map->square + move - 1)->getToStart() == number - 1 && (map->square + move - 1)->getType() != Type::Wall)
		(map->square + move)->setParent(move - 1);
	else if ((map->square + move + 1)->getToStart() == number - 1 && (map->square + move + 1)->getType() != Type::Wall)
		(map->square + move)->setParent(move + 1);
	//
	number++;
	if ((map->square + move - 64)->getType() == Type::Path || (map->square + move - 64)->getType() == Type::Direction) {
		if ((map->square + move - 64)->getToStart() == 0 || (map->square + move - 64)->getToStart() > number) {
			(map->square + move - 64)->setToStart(number);
			(map->square + move - 64)->setToEnd(map->square + endNode);
		}
		(map->square + move - 64)->setType(Type::Direction);
	}
	if ((map->square + move + 64)->getType() == Type::Path || (map->square + move + 64)->getType() == Type::Direction) {
		if ((map->square + move + 64)->getToStart() == 0 || (map->square + move + 64)->getToStart() > number) {
			(map->square + move + 64)->setToStart(number);
			(map->square + move + 64)->setToEnd(map->square + endNode);
		}
		(map->square + move + 64)->setType(Type::Direction);
	}
	if ((map->square + move + 1)->getType() == Type::Path || (map->square + move + 1)->getType() == Type::Direction) {
		if ((map->square + move + 1)->getToStart() == 0 || (map->square + move + 1)->getToStart() > number) {
			(map->square + move + 1)->setToStart(number);
			(map->square + move + 1)->setToEnd(map->square + endNode);
		}
		(map->square + move + 1)->setType(Type::Direction);
	}
	if ((map->square + move - 1)->getType() == Type::Path || (map->square + move - 1)->getType() == Type::Direction) {
		if ((map->square + move - 1)->getToStart() == 0 || (map->square + move - 1)->getToStart() > number) {
			(map->square + move - 1)->setToStart(number);
			(map->square + move - 1)->setToEnd(map->square + endNode);
		}
		(map->square + move - 1)->setType(Type::Direction);
	}
	//
	if ((map->square + move - 64)->getType() == Type::Stop || (map->square + move + 64)->getType() == Type::Stop ||
		(map->square + move + 1)->getType() == Type::Stop || (map->square + move - 1)->getType() == Type::Stop) {
		stop = true;
		length = (map->square + move)->getToStart();
		lengthCopy = length;
		road = new int[length];
		*road = move;
		for (int i = 1; i < length; i++) {
			*(road + i) = (map->square + *(road + (i - 1)))->getParent();
		}
	}
}

void PathFinder::run() {
	if (start == true && stop == false) {
		if ((map->square + startNode - 64)->getType() != Type::Wall) {
			(map->square + startNode - 64)->setToStart(map->square + startNode);
			(map->square + startNode - 64)->setToEnd(map->square + endNode);
			(map->square + startNode - 64)->setType(Type::Direction);
			(map->square + startNode - 64)->setParent(startNode);
		}
		if ((map->square + startNode + 64)->getType() != Type::Wall) {
			(map->square + startNode + 64)->setToStart(map->square + startNode);
			(map->square + startNode + 64)->setToEnd(map->square + endNode);
			(map->square + startNode + 64)->setType(Type::Direction);
			(map->square + startNode + 64)->setParent(startNode);
		}
		if ((map->square + startNode + 1)->getType() != Type::Wall) {
			(map->square + startNode + 1)->setToStart(map->square + startNode);
			(map->square + startNode + 1)->setToEnd(map->square + endNode);
			(map->square + startNode + 1)->setType(Type::Direction);
			(map->square + startNode + 1)->setParent(startNode);
		}
		if ((map->square + startNode - 1)->getType() != Type::Wall) {
			(map->square + startNode - 1)->setToStart(map->square + startNode);
			(map->square + startNode - 1)->setToEnd(map->square + endNode);
			(map->square + startNode - 1)->setType(Type::Direction);
			(map->square + startNode - 1)->setParent(startNode);
		}
		start = false;
	}
	else if (stop) {
		if (!(lengthCopy <= 0)) {
			lengthCopy--;
			(map->square + *(road + lengthCopy))->setType(Type::CorrectWay);
			if (lengthCopy == 0) clock.restart();
		}
		else if(!start && clock.getElapsedTime().asSeconds() >= 1) {
			map->reset();
			lengthCopy = length;
			start = true;
		}
		return;
	}
	else {
		int move(0);
		for (int i = 0; i < 2304; i++) {
			move = checkMove(move, i);
		}
		if (move == 0) return;
		makeMove(move);
	}
}

void PathFinder::reset() {
	length = 0;
	lengthCopy = 0;

	if(length != 0)	delete [] road;

	start = true;
	stop = false;

	for (int i = 0; i < 2304; i++) {
		if ((map->square + i)->getType() == Type::Start) startNode = i;
		else if ((map->square + i)->getType() == Type::Stop) endNode = i;
	}
}

PathFinder::~PathFinder() {
	delete [] road;
}