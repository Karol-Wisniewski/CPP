#include <iostream>
#include "../headers/Position.h"
#include "../headers/World.h"
#include "../headers/Sheep.h"
#include "../headers/Wolf.h"
#include "../headers/Toadstool.h"
#include "../headers/Dandelion.h"
#include "../headers/Grass.h"

using namespace std;

int main()
{
	
	// World test
	srand(time(0));
	World* world = new World();
	Position posP1{ 0, 0 };
	Position posP2{ 0, 2 };
	Position posP3{ 1, 2 };
    Position posP4{ 4, 3 };
	Position posP5{ 5, 5 };
    Position posP6{5, 4};
	Wolf wolf1{ posP1, world };
	Wolf wolf2{ posP3, world };
	Wolf wolf3{ posP4, world };
    Sheep sheep1{ posP5, world };
    Grass grass1{ posP6, world };
    Toadstool toadstool1{ posP2, world };
    world->addOrganism(&sheep1);
    world->addOrganism(&grass1);
	world->addOrganism(&wolf1);
    world->addOrganism(&toadstool1);
	world->addOrganism(&wolf2);
	world->addOrganism(&wolf3);
	


	// Tura 0
	cout << world->toString() << endl;

	// Tura 1
	world->setTurn(1);
	world->makeTurn();
	cout << world->toString() << endl;

	// Tura 2
	world->makeTurn();
	cout << world->toString() << endl;

    cout << "Writing world to world.bin..." << endl;
	world->writeWorld("world.bin");

	// Tura 3
	
	world->makeTurn();
	cout << world->toString() << endl;

	// Tura 4
	world->makeTurn();
	cout << world->toString() << endl;

	// Tura 5
	world->makeTurn();
	cout << world->toString() << endl;

	// powrot do Tury 2
    cout << "Reading world from world.bin..." << endl;
	world->readWorld("world.bin");
	cout << world->toString() << endl;

	return 0;
}