#ifndef __FACTORIES__
#define __FACTORIES__

#include "ships.h"
#include "guns.h"

using namespace std;

class AbstractFactory
{
protected:
	string color;
	int r, w, h, diff_between_ships, count, x, y, angle;
public:
	AbstractFactory(string color, int diff_between_ships);
	virtual Gun * create_gun() = 0;
	virtual SpaceShip * create_ship() = 0;
	void update_ships_count(int count);
};

class BomberFactory:public AbstractFactory
{
public:
	BomberFactory(string color, int diff_between_ships = 100) : AbstractFactory(color, diff_between_ships)
	{
		r = 30;
		w = 10;
		h = 30;
	}
	Gun * create_gun() override;
	SpaceShip * create_ship() override;
};

class FighterFactory:public AbstractFactory
{
public:
	FighterFactory(string color, int diff_between_ships = 100) : AbstractFactory(color, diff_between_ships)
	{
		r = 15;
		w = 5;
		h = 12;
	}
	Gun * create_gun() override;
	SpaceShip * create_ship() override;
};

class CruiserFactory:public AbstractFactory
{
public:
	CruiserFactory(string color, int diff_between_ships = 100) : AbstractFactory(color, diff_between_ships)
	{
		r = 25;
		w = 10;
		h = 20;
	}
	Gun * create_gun() override;
	SpaceShip * create_ship() override;
};
#endif
