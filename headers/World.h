#pragma once
#include <vector>
#include <ctime>
#include <algorithm>
#include <string>


using namespace std;

class Organism;
class Position;
class World
{
private:
	int worldX;
	int worldY;
	int turn = 0;
	// Use vector of pointers to Organism class, so that we can store the derived class
	vector<Organism*> organisms;
	vector<Organism*> deadOrganisms;
	char separator = '-';

public:
	World(int worldX, int worldY);
	World() : World(6, 6) {};

	int getWorldX();
	void setWorldX(int worldX);
	int getWorldY();
	void setWorldY(int worldY);

	int getTurn();
	void setTurn(int turn);
	
	void addOrganism(Organism *organism);
	void removeOrganism(Organism *organism);
	vector<Position> getVectorOfFreePositionsAround(Position position);
	vector<Position> getVectorOfPositionsAround(Position position);
	void makeTurn();

	void writeWorld(string fileName);
	void readWorld(string fileName);
	
	string toString();

	string getOrganismSymbolFromPosition(Position position);
	Organism* getOrganismFromPosition(Position position);
	bool isPositionOnWorld(Position position);
	bool isPositionFree(Position position);

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & worldX;
        ar & worldY;
        ar & turn;
        ar & organisms;
    }
};