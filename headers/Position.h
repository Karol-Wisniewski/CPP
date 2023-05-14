#pragma once
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class Position {
private:
	int x;
	int y;

public:
	Position(int x, int y);
	Position() : x(0), y(0) {}

	int getX();
	void setX(int x);
	int getY();
	void setY(int y);

	string toString();

	double distance(Position position);
	void move(int dx, int dy);

	bool operator == (Position position)
	{
		return (this->getX() == position.getX() && this->getY() == position.getY());
	}

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& x;
        ar& y;
    }
};