#include "../headers/Animal.h"
#include <iostream>


Animal::Animal(int power, int initiative, int liveLength, int powerToReproduce, World* world, Position position) : Organism(power, initiative, liveLength, powerToReproduce, world, position) {};

void Animal::action()
{
	setPower(power + 1);

	setLiveLength(liveLength - 1);

	if (liveLength <= 0) {
		this->setToBeKilled(true);
		return;
	}

	int currentX = position.getX();
	int currentY = position.getY();

	int dx;
	int dy;

	Position newPosition;

	vector<Position> potentialPositions = world->getVectorOfPositionsAround(position);

	auto comparePositions = [](Position& p1, Position& p2)
	{
		if (p1.getX() != p2.getX()) {
			return p1.getX() < p2.getX(); // sort by x coordinate first
		}
		return p1.getY() < p2.getY(); // then sort by y coordinate
	};

	std::sort(potentialPositions.begin(), potentialPositions.end(), comparePositions);


	

	potentialPositions.erase(unique(potentialPositions.begin(), potentialPositions.end()), potentialPositions.end());
	//remove position if its the current position
	potentialPositions.erase(std::remove_if(potentialPositions.begin(), potentialPositions.end(), [this](Position pos) {
		return pos == position;
	}), potentialPositions.end());

	// std::cout << "Potential positions for " << getSpecies() << " at (" << currentX << ", " << currentY << "):" << std::endl;
	// for (int i = 0; i < potentialPositions.size(); i++) {
	// 	std::cout << potentialPositions[i].toString() << std::endl;
	// }



	if (potentialPositions.empty()) {
		return;
	} else {
		newPosition = potentialPositions[rand() % potentialPositions.size()];
		dx = newPosition.getX() - currentX;
		dy = newPosition.getY() - currentY;
		if (world->isPositionFree(newPosition)) {
			move(dx,dy);
		}
		else {
			collision(world->getOrganismFromPosition(newPosition));
		}
	}
};