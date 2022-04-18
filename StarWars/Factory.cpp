#include "Factory.h"

AbstractFactory::AbstractFactory(string color, int diff_between_ships) 
	:color(color), diff_between_ships(diff_between_ships)
{
	count = 0;
	x = 50;
	y = 50;
	if (color == "red")
	{
		y = y;
		angle = 180;
	}
	else if (color == "blue")
	{
		y = 1080 - y;  // TODO change to check screen revolution
		angle = 0;
	}
	else
		cout << "unexpected color!! Change that -> color: " << color << endl;
}

void AbstractFactory::update_ships_count(int count)
{
	this->count = count;
}

Gun BomberFactory::create_gun()
{
	int concrete_x = x - r + diff_between_ships * count;
	BomberGun b_gun = BomberGun("bomber", 80, concrete_x, y, angle, w, h);
	return b_gun;
}

BomberShip BomberFactory::create_ship()
{
	Gun gun = create_gun();
	int concrete_ship_x = x + diff_between_ships * count;
	string type = "bomber";
	BomberShip b_ship = BomberShip(300, 2, (float)0.2, (float)0.3, type, color, concrete_ship_x, y, angle, r, &gun);
	return b_ship;
}

Gun FighterFactory::create_gun()
{
	int concrete_x = x - r + diff_between_ships * count;
	FighterGun b_gun = FighterGun("fighter", 30, concrete_x, y, angle, w, h);
	return b_gun;
}

FighterShip FighterFactory::create_ship()
{
	Gun gun = create_gun();
	int concrete_ship_x = x + diff_between_ships * count;
	string type = "fighter";
	FighterShip b_ship = FighterShip(200, 2, (float)0.5, (float)0.1, type, color, concrete_ship_x, y, angle, r, &gun);
	return b_ship;
}

Gun CruiserFactory::create_gun()
{
	int concrete_x = x - r + diff_between_ships * count;
	CruiserGun b_gun = CruiserGun("cruiser", 60, concrete_x, y, angle, w, h);
	return b_gun;
}

CruiserShip CruiserFactory::create_ship()
{
	Gun gun = create_gun();
	int concrete_ship_x = x + diff_between_ships * count;
	string type = "cruiser";
	CruiserShip b_ship = CruiserShip(250, 2, (float)0.1, (float)0.4, type, color, concrete_ship_x, y, angle, r, &gun);
	return b_ship;
}
