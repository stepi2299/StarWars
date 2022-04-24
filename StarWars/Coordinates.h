#ifndef __Coordinates__
#define __Coordinates__
#include <iostream>

using namespace std;

class Coordinates
{
private:
	double default_angle;
	double battle_angle;
public:
	int x, y, w, h;
	double angle;
	Coordinates();
	Coordinates(int x, int y, double angle, int w, int h);
	~Coordinates() {}
	double get_def_angl();
	void set_battle_angle(double b_angle);
	double get_battle_angle();
};

class ShipCoordinates
{
private:
	int default_angle;
public:
	int x, y, r, angle;
	ShipCoordinates();
	ShipCoordinates(int x, int y, int angle, int r);
	~ShipCoordinates() {}
	int get_def_angl();
};

class AmmoCoordinates
{
private:
	double angle;
public:
	int w, h;
	double x, y;
	AmmoCoordinates();
	AmmoCoordinates(double x, double y, double angle, int w, int h);
	~AmmoCoordinates() {}
	double get_def_angl();
};
#endif

