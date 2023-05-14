#include "../headers/World.h"
#include "../headers/Organism.h"
#include <fstream>
#include <iostream>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>

string World::getOrganismSymbolFromPosition(Position position)
{	
	for (Organism* org : organisms) {
		Position organismPosition = org->getPosition();
		if (organismPosition == position) return org->getSpecies();
	}
	return "";
	//Instead of using organism object, we can refer to organism abstract class pointer and use the -> operator
}

Organism* World::getOrganismFromPosition(Position position)
{	
	for (Organism* org : organisms) {
		Position organismPosition = org->getPosition();
		if (organismPosition == position) return org;
	}
	return nullptr;
	//Instead of using organism object, we can refer to organism abstract class pointer and use the -> operator
}

bool World::isPositionOnWorld(Position position)
{
	return (position.getX() >= 0 && position.getY() >= 0 && position.getX() < getWorldX() && position.getY() < getWorldY());
}

bool World::isPositionFree(Position position) {
	return this->getOrganismSymbolFromPosition(position).empty();
}

vector<Position> World::getVectorOfFreePositionsAround(Position position)
{	
	int pos_x = position.getX(), pos_y = position.getY();
	vector<Position> result;
	for(int x = -1; x < 2; ++x)
		for (int y = -1; y < 2; ++y)
			if ((x != 0 || y != 0) && 
				isPositionOnWorld(Position(pos_x + x, pos_y + y))) {
				result.push_back(Position(pos_x + x, pos_y + y));
			}
	auto iter = remove_if(result.begin(), result.end(),
		[this](Position pos) {return !isPositionFree(pos);});

	result.erase(iter, result.end());

	return result;
}

vector<Position> World::getVectorOfPositionsAround(Position position)
{	
	int pos_x = position.getX(), pos_y = position.getY();
	vector<Position> result;
	for(int x = -1; x < 2; ++x) {
		for (int y = -1; y < 2; ++y) {
			if ((x != 0 || y != 0) && isPositionOnWorld(Position(pos_x + x, pos_y + y))) {
				result.push_back(Position(pos_x + x, pos_y + y));
			};
		}
	}
	return result;
}

World::World(int worldX, int worldY)
{
	setWorldX(worldX);
	setWorldY(worldY);
}

int World::getWorldX()
{
	return this->worldX;
}

void World::setWorldX(int worldX)
{
	this->worldX = worldX;
}

int World::getWorldY()
{
	return this->worldY;
}

void World::setWorldY(int worldY)
{
	this->worldY = worldY;
}

void World::setTurn(int turn)
{
	this->turn = turn;
}

int World::getTurn()
{
	return this->turn;
}

void World::addOrganism(Organism* organism) {
	std::cout << "Adding " << organism->getSpecies() << " to world at position (" << organism->getPosition().getX() << ", " << organism->getPosition().getY() << ")\n";
	organisms.push_back(organism);
}


void World::removeOrganism(Organism* organism)
{
	std::cout << "Removing " << organism->getSpecies() << " from world at position (" << organism->getPosition().getX() << ", " << organism->getPosition().getY() << ")\n";
	for(int i = 0; i < organisms.size(); i++) {
		Organism* org = organisms[i];
		for(Ancestor* ancestor : org->getAncestors()) {
			if (ancestor->ancestor == organism) {
				ancestor->turnOfDeath = turn;
			}
		}
	}
	organisms.erase(std::remove(organisms.begin(), organisms.end(), organism), organisms.end());
	deadOrganisms.push_back(organism);
}

void World::makeTurn()
{
	//Sort organisms by initiative
	if (organisms.size() > 1) {
		sort(organisms.begin(), organisms.end(), [](Organism* first, Organism* second) {
			return first->getInitiative() > second->getInitiative();
		});
	}
	//Make turn for each organisms if they haven't moved or are not being killed
	int i = 0;
	for (i ; i < organisms.size(); i++) {
		Organism* org = organisms[i];
		// std::cout << "Ancestors of " << org->getSpecies() << " at position "<< "(" <<org->getPosition().getX() << ", " << org->getPosition().getY() << ")" <<":\n";
		for(int j = 0; j < org->getAncestors().size(); j++) {
			std::cout << org->getAncestors()[j]->ancestor->getSpecies() << " " << org->getAncestors()[j]->turnOfBirth << " " << org->getAncestors()[j]->turnOfDeath << "\n";
		}
		if (!org->getHasMoved() && !org->getToBeKilled()) {
			std::cout << "Making turn for " << org->getSpecies() << " at position (" << org->getPosition().getX() << ", " << org->getPosition().getY() << ")\n";
			org->action();
			org->setHasMoved(true);
		}
	}
	//Kill organisms and reset hasMoved flag
	for(int i = organisms.size()- 1; i >= 0 ;i--) {
		Organism* org = organisms[i];
		if (org->getToBeKilled() == true) {
			removeOrganism(org);
		}
		else org->setHasMoved(false);
	}
	this->turn++;
}

void World::writeWorld(std::string fileName) {
	cout << "Writing world to file " << fileName << "\n";
    std::ofstream outFile(fileName, std::ios::binary);
	cout << "File opened\n";
    boost::archive::binary_oarchive outArchive(outFile);
	cout << "Archive created\n";
    outArchive << *this;
	cout << "Archive written\n";
    outFile.close();
	cout << "File closed\n";
}


void World::readWorld(std::string fileName) {
	cout << "Reading world from file " << fileName << "\n";
    std::ifstream inFile(fileName, std::ios::binary);
	cout << "File opened\n";
    boost::archive::binary_iarchive inArchive(inFile);
	cout << "Archive created\n";
    inArchive >> *this;
	cout << "Archive read\n";
    inFile.close();
	cout << "File closed\n";
}

string World::toString()
{
	string result = "\nturn: " + to_string(getTurn()) + "\n";
	string spec;

	for (int wY = 0; wY < getWorldY(); ++wY) {
		for (int wX = 0; wX < getWorldX(); ++wX) {
			spec = getOrganismSymbolFromPosition(Position(wX, wY));
			if (spec != "")
				result += spec;
			else
				result += separator;
		};
		result += "\n";
	}
	return result;
}