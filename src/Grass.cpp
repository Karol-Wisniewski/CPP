#include "../headers/Grass.h"
#include <iostream>

Grass::Grass(Position position, World* world) : Plant(0, 0, 6, 3, world, position)
{
    setSpecies("G");
}

Grass::Grass(Grass* grass, Position position) : Plant(
	grass->getPower(), 
	grass->getInitiative(), 
	grass->getLiveLength(), 
	grass->getPowerToReproduce(), 
	grass->getWorld(),
	position)
{
	setSpecies(grass->getSpecies());
	setTurnOfBirth(world->getTurn());
}

void Grass::clone(Organism* parent)
{
	vector<Position> freePositions = world->getVectorOfFreePositionsAround(this->position);
	if	(!freePositions.empty()) {
		Position childPosition = freePositions[rand() % freePositions.size()];
		Grass* child = new Grass(this, childPosition);
		child->setHasMoved(true);
        child->setAncestors(parent->getAncestors());
        Ancestor* ancestor = new Ancestor{parent, parent->getTurnOfBirth(), -1};
        child->addAncestor(ancestor);
        world->addOrganism(child);
	} else {
        std::cout << "No free positions around for a child of " << species << " to clone." << std::endl;
        return;
    }
}

BOOST_CLASS_EXPORT(Grass);