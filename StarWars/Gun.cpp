#include "Gun.h"
Gun::Gun()
{
	cout << "Gun" << endl;
}

Gun::Gun(string type, int period, int x, int y, int angle, int w, int h):
	type(type), period(period), coordinates(x, y, angle, w, h)
{
	damage = (rand() % 10) + min_damage;
}

string Gun::get_type()
{
	return type;
}

Coordinates Gun::get_coordinates()
{
	return coordinates;
}

Ammunition Gun::attack(SpaceShip *ship)
{
	ShipCoordinates target_coord = ship->get_coordinates();
	//Ammunition ammo = Ammunition(damage, period, fast,)  think about coordinates (center, left_bottom etc.)
}
