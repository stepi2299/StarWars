#ifndef __Coordinates__
#define __Coordinates__
#include <iostream>

using namespace std;

class Coordinates
{
public:
	int x, y, w, h, angle;
	Coordinates();
	Coordinates(int x, int y, int angle, int w, int h);
	~Coordinates() {}
};

class ShipCoordinates
{
public:
	int x, y, r, angle;
	ShipCoordinates();
	ShipCoordinates(int x, int y, int angle, int r);
	~ShipCoordinates() {}
};
#endif

