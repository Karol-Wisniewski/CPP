#pragma once
#include "Position.h"
#include "World.h"
// Directions are: 0 - left, 1 - right, 2 - up, 3 - down
// #define DIRECTIONS 4

using namespace std;

struct Ancestor {
	Organism* ancestor;
	int turnOfBirth;
	int turnOfDeath;

    template <class Archive> void serialize(Archive& ar, const unsigned int version)
    {
        ar& ancestor;
        ar& turnOfBirth;
        ar& turnOfDeath;
    }
};

class Organism
{
// changed private to protected so that the derived classes can access the variables
protected:
	int power;
	int initiative;
	int liveLength;
	int powerToReproduce;
	bool hasMoved;
	bool toBeKilled;
	int turnOfBirth;
	World* world;
	Position position;
	string species;
	vector<Ancestor*> ancestors;
	
public:
	Organism(int power, int initiative, int liveLength, int powerToReproduce, World* world, Position position);
    Organism(){};
	int getPower();
	void setPower(int power);
	int getInitiative();
	void setInitiative(int initiative);
	int getLiveLength();
	void setLiveLength(int liveLength);
	int getPowerToReproduce();
	void setPowerToReproduce(int powerToReproduce);
	World* getWorld();
	void setWorld(World* world);
	Position getPosition();
	void setPosition(Position position);
	string getSpecies();
	void setSpecies(string spec);
	bool getHasMoved();
	void setHasMoved(bool hasMoved);
	bool getToBeKilled();
	void setToBeKilled(bool toBeKilled);
	void setAncestors(vector<Ancestor*> ancestors);
	void addAncestor(Ancestor* ancestor);
	vector<Ancestor*> getAncestors();
	void setTurnOfBirth(int turnOfBirth);
	int getTurnOfBirth();

	string toString();
	
	// define at lest one pure virtual function, so that the Organism class is abstract
	virtual void move(int dx, int dy);
	virtual void action() = 0;
	virtual void collision(Organism* other);
	virtual void clone(Organism* parent) = 0;
    virtual ~Organism(){};

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& power;
        ar& initiative;
        ar& liveLength;
        ar& powerToReproduce;
        ar& hasMoved;
        ar& toBeKilled;
        ar& turnOfBirth;
        ar& position;
        ar& species;
        ar& ancestors;
    }
};