#include "../headers/Organism.h"
#include "../headers/World.h"
#include <iostream>

Organism::Organism(int power, int initiative, int liveLength, int powerToReproduce, World* world, Position position)
{
	setPosition(position);
	setWorld(world);
	setPower(power);
	setInitiative(initiative);
	setLiveLength(liveLength);
	setPowerToReproduce(powerToReproduce);
	setSpecies("O");
	setHasMoved(false);
	setToBeKilled(false);
	setAncestors(vector<Ancestor*> {});
	setTurnOfBirth(world->getTurn());
}

void Organism::setTurnOfBirth(int turnOfBirth)
{
	this->turnOfBirth = turnOfBirth;
	// std::cout << "Organism " << this->getSpecies() << " born at turn " << turnOfBirth << std::endl;
}

int Organism::getTurnOfBirth()
{
	return this->turnOfBirth;
}

void Organism::addAncestor(Ancestor* ancestor)
{
	this->ancestors.push_back(ancestor);
}

void Organism::setAncestors(vector<Ancestor*> ancestorsArg)
{
	for (int i = 0; i < ancestorsArg.size(); i++) {
		this->ancestors.push_back(ancestorsArg[i]);
	}
}

vector<Ancestor*> Organism::getAncestors()
{
	return this->ancestors;
}

int Organism::getPower()
{
	return this->power;
}

bool Organism::getToBeKilled()
{
	return this->toBeKilled;
}

void Organism::setToBeKilled(bool toBeKilled)
{
	this->toBeKilled = toBeKilled;
}

void Organism::setPower(int power)
{
	this->power = power;
}

bool Organism::getHasMoved()
{
	return this->hasMoved;
}

void Organism::setHasMoved(bool hasMoved)
{
	this->hasMoved = hasMoved;
}

Position Organism::getPosition()
{
	return this->position;
}

void Organism::setPosition(Position position)
{
	this->position = position;
}

string Organism::toString()
{
	return "{ species: " + this->getSpecies() + 
		", power: " + to_string(getPower()) + 
		", position: " + getPosition().toString() + "}";
}

string Organism::getSpecies()
{
	return this->species;
}

void Organism::setSpecies(string spec)
{
	this->species = spec;
}

int Organism::getLiveLength()
{
	return this->liveLength;
}

void Organism::setLiveLength(int liveLength) {
	this->liveLength = liveLength;
}

int Organism::getInitiative()
{
	return this->initiative;
}

void Organism::setInitiative(int initiative)
{
	this->initiative = initiative;
}

int Organism::getPowerToReproduce()
{
	return this->powerToReproduce;
}

void Organism::setPowerToReproduce(int powerToReproduce)
{
	this->powerToReproduce = powerToReproduce;
}

World* Organism::getWorld()
{
	return this->world;
}

void Organism::setWorld(World* world)
{
	this->world = world;
}

void Organism::collision(Organism* other)
{
	Position otherPosition = other->getPosition();

	bool canOtherReproduce = other->getPower() >= other->getPowerToReproduce();

	bool canThisReproduce = power >= powerToReproduce;

	if (other->getSpecies() == species && !other->getHasMoved() && canOtherReproduce && canThisReproduce) {
		this->clone(other);
		setPower(power / 2);
		other->setPower(other->getPower() / 2);
		other->setHasMoved(true);
		return;
	}
	else if (other->getSpecies() == species) {
		std::cout << species << " at position " << "(" << position.getX() << ", " << position.getY() << ")" << " and " << other->getSpecies() << " at position " << "(" << other->getPosition().getX() << ", " << other->getPosition().getY() << ")" << " cannot reproduce right now" << std::endl;
		return;
	}
	// Killing
	else if (other->getSpecies() == "T") {
		std::cout << species << " ate " << other->getSpecies() << " and died" << std::endl;
		this->setToBeKilled(true);
		other->setToBeKilled(true);
	}
	else {
		if (other->getPower() < power) {
			std::cout << species << " killed " << other->getSpecies() << std::endl;
			other->setToBeKilled(true);
		}
		else {
            std::cout << species << " came across " << other->getSpecies() << " and got killed " << std::endl;
			this->setToBeKilled(true);
		}
	}
	return;
}

void Organism::move(int dx, int dy)
{
    position.move(dx, dy);
	std::cout << species << " moved by " << "(" << dx << ", " << dy << ")" << std::endl;
}
