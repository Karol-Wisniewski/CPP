#include "../headers/Wolf.h"
#include <iostream>

Wolf::Wolf(Position position, World* world) : Animal(8, 5, 20, 16, world, position)
{
	setSpecies("W");
};

Wolf::Wolf(Wolf* wolf, Position position) : Animal(
    wolf->getPower(), 
    wolf->getInitiative(), 
    20, //Wolf's liveLength
    wolf->getPowerToReproduce(), 
    wolf->getWorld(),
    position)
{
	setSpecies(wolf->getSpecies());
};

void Wolf::clone(Organism* parent)
{
    parent->setLiveLength(parent->getLiveLength() - 1);
    vector<Position> freePositions = world->getVectorOfFreePositionsAround(position);
    if (!freePositions.empty()) {
        Position childPosition = freePositions[rand() % freePositions.size()];

        Wolf* child = new Wolf(childPosition, world);
        child->setHasMoved(true);
        child->setAncestors(this->getAncestors());
        child->setAncestors(parent->getAncestors());
        Ancestor* firstAncestor = new Ancestor{this, this->getTurnOfBirth(), -1};
        Ancestor* secondAncestor = new Ancestor{parent, parent->getTurnOfBirth(), -1};
        child->addAncestor(firstAncestor);
        child->addAncestor(secondAncestor);
        world->addOrganism(child);
    } else {
        std::cout << "No free positions around for a child of " << species << " to clone." << std::endl;
        return;
    }
}

BOOST_CLASS_EXPORT(Wolf);