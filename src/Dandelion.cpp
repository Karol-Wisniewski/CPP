#include "../headers/Dandelion.h"
#include <iostream>

Dandelion::Dandelion(Position position, World* world) : Plant(0, 0, 6, 2, world, position)
{
	setSpecies("D");
}

Dandelion::Dandelion(Dandelion* dandelion, Position position) : Plant(
	dandelion->getPower(), 
	dandelion->getInitiative(), 
	dandelion->getLiveLength(), 
	dandelion->getPowerToReproduce(), 
	dandelion->getWorld(), 
	position)
{
	setSpecies("D");
	setTurnOfBirth(world->getTurn());
}

void Dandelion::clone(Organism* parent)
{
	vector<Position> freePositions = world->getVectorOfFreePositionsAround(this->position);
	if	(!freePositions.empty()) {
		Position childPosition = freePositions[rand() % freePositions.size()];
		Dandelion* child = new Dandelion(this, childPosition);
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

BOOST_CLASS_EXPORT(Dandelion);