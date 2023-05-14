#include "../headers/Sheep.h"
#include <iostream>

Sheep::Sheep(Position position, World* world) : Animal(3, 3, 10, 6, world, position)
{
    setSpecies("S");
}
Sheep::Sheep(Sheep* sheep, Position position) : Animal(
    sheep->getPower(), 
    sheep->getInitiative(), 
    sheep->getLiveLength(), 
    sheep->getPowerToReproduce(), 
    sheep->getWorld(),
    position) 
{
	setSpecies("S");
    setTurnOfBirth(world->getTurn());
};

void Sheep::clone(Organism* parent)
{
	vector<Position> freePositions = world->getVectorOfFreePositionsAround(this->position);
	if	(!freePositions.empty()) {
		Position childPosition = freePositions[rand() % freePositions.size()];

		Sheep* child = new Sheep(this, childPosition);
		child->setHasMoved(true);
        child->setAncestors(this->getAncestors());
        Ancestor* firstAncestor = new Ancestor{this, this->getTurnOfBirth(), -1};
        Ancestor* secondAncestor = new Ancestor{parent, parent->getTurnOfBirth(), -1};
        child->addAncestor(firstAncestor);
        child->setAncestors(parent->getAncestors());
        child->addAncestor(secondAncestor);
        world->addOrganism(child);

	} else {
        std::cout << "No free positions around for a child of " << species << " to clone." << std::endl;
        return;
    }
}

BOOST_CLASS_EXPORT(Sheep);