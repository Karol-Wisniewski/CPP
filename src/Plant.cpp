#include "../headers/Plant.h"

Plant::Plant(int power, int initiative, int liveLength, int powerToReproduce, World* world, Position position) : Organism(power, initiative, liveLength, powerToReproduce, world, position) {};

void Plant::action()
{
	if (rand() % 100 < 10) {
		vector<Position> freePositions = world->getVectorOfFreePositionsAround(this->position);
		if	(!freePositions.empty()) {
			this->clone(this);
		} else {
			return;
		}
	}
}