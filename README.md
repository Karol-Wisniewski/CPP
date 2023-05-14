# Living World Project


This project represents a living world simulation made for university purposes. 


The project is written in C++ and uses boost libraries for serialization and deserialization of the world state.


1. There are two types of entities: plants and animals.

2. Animals can move around and eat plants.

3. Organisms can reproduce and fight each other (despite the plants).

4. The world is a 2D grid with a fixed size.

5. The world is surrounded by a wall that cannot be passed through.

6. Each organism has fixed statistics: power, initiative, powerToReproduce, liveLength, ancestors, position and world

7. Each organism has a symbol that represents it on the map.

8. The world "lives" thanks to turns. Each turn is a new state of the world.

9. Each turn, each organism can make one move.

10. There are some special abilities that can be used by organisms. For example, when an animal eats a Toadstool, it dies.

11. Implemented organisms are: Wolf, Sheep, Grass, Dandelion, Toadstool.

12. After each turn, the liveLength of each organism is decreased by 1 and its power is increased by 1.


The whole project was written using CLion IDE.