#include "Factory.h"

AbstractFactory::AbstractFactory(string color, int diff_between_ships, sf::Vector2i win_dims) 
	:color(color), diff_between_ships(diff_between_ships), win_dims(win_dims)
{
	count = 0;
	x = diff_between_ships;
	int temp_y = 100;
	if (color == "red")
	{
		y = temp_y;
		angle = 0;
	}
	else if (color == "blue")
	{
		y = win_dims.y - temp_y;
		angle = 180;
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
	int concrete_x = x + diff_between_ships * count;
	Gun* b_gun = new BomberGun("bomber", 80, concrete_x, y, angle, w, h, color, r);
	return b_gun;
}

SpaceShip* BomberFactory::create_ship()
{
	Gun* gun = create_gun();
	int concrete_ship_x = x + diff_between_ships * count;
	string type = "bomber";
	SpaceShip* b_ship = new BomberShip(600, 2, 2, 3, type, color, concrete_ship_x, y, angle, r, gun);
	return b_ship;
}

Gun* FighterFactory::create_gun()
{
	int concrete_x = x + diff_between_ships * count;
	Gun* b_gun = new FighterGun("fighter", 30, concrete_x, y, angle, w, h, color, r);
	return b_gun;
}

SpaceShip* FighterFactory::create_ship()
{
	Gun* gun = create_gun();
	int concrete_ship_x = x + diff_between_ships * count;
	string type = "fighter";
	SpaceShip* f_ship = new FighterShip(400, 2, 5, 1, type, color, concrete_ship_x, y, angle, r, gun);
	return f_ship;
}

Gun* CruiserFactory::create_gun()
{
	int concrete_x = x + diff_between_ships * count;
	Gun* b_gun = new CruiserGun("cruiser", 60, concrete_x, y, angle, w, h, color, r);
	return b_gun;
}

SpaceShip* CruiserFactory::create_ship()
{
	Gun* gun = create_gun();
	int concrete_ship_x = x + diff_between_ships * count;
	string type = "cruiser";
	SpaceShip* c_ship = new CruiserShip(500, 2, 1, 4, type, color, concrete_ship_x, y, angle, r, gun);
	return c_ship;
}
