#include "../headers/Toadstool.h"
#include <iostream>

Toadstool::Toadstool(Position position, World* world) : Plant(0, 0, 12, 4, world, position) {
	setSpecies("T");
};

Toadstool::Toadstool(Toadstool* toadstool, Position position) : Plant(
    toadstool->getPower(), 
    toadstool->getInitiative(), 
    toadstool->getLiveLength(), 
    toadstool->getPowerToReproduce(), 
    toadstool->getWorld(),
    position) 
{
	setSpecies("T");
    setTurnOfBirth(world->getTurn());
};

void Toadstool::clone(Organism* parent)
{
	vector<Position> freePositions = world->getVectorOfFreePositionsAround(this->position);
	if	(!freePositions.empty()) {
		Position childPosition = freePositions[rand() % freePositions.size()];
		Toadstool* child = new Toadstool(this, childPosition);
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

BOOST_CLASS_EXPORT(Toadstool);