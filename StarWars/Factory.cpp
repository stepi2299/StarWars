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

Gun* BomberFactory::create_gun()
{
	int concrete_x = x - r + diff_between_ships * count;
	BomberGun b_gun = BomberGun("bomber", 80, concrete_x, y, angle, w, h);
	return &b_gun;
}

SpaceShip* BomberFactory::create_ship()
{
	Gun* gun = create_gun();
	int concrete_ship_x = x + diff_between_ships * count;
	string type = "bomber";
	BomberShip b_ship = BomberShip(300, 2, (float)0.2, (float)0.3, type, color, concrete_ship_x, y, angle, r, gun);
	return &b_ship;
}
