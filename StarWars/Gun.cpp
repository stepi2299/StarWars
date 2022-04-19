#include "Gun.h"
Gun::Gun()
{
	cout << "Gun" << endl;
}

Gun::Gun(string type, int period, int x, int y, int angle, int w, int h, string color, int r):
	type(type), period(period), coordinates(x, y, angle, w, h), color(color), r(r)
{
	if (color == "red")
		sf_color = sf::Color::Red;
	else
		sf_color = sf::Color::Blue;
}

string Gun::get_type()
{
	return this->type;
}

Coordinates Gun::get_coordinates()
{
	return coordinates;
}

Ammunition Gun::attack(SpaceShip *ship)
{
	ShipCoordinates target_coord = ship->get_coordinates();
	return Ammunition();
	//Ammunition ammo = Ammunition(damage, period, fast,)  think about coordinates (center, left_bottom etc.)
}

sf::RectangleShape Gun::draw()
{
	sf::RectangleShape rec = sf::RectangleShape(sf::Vector2f(coordinates.w, coordinates.h));
	rec.setOrigin(-r, 0);
	rec.setPosition(coordinates.x, coordinates.y);
	rec.setFillColor(sf_color);
	rec.setRotation((float)coordinates.angle);
	return rec;
}

void Gun::update_coord_gun(int x, int y, int ang)
{
	coordinates.x += x;
	coordinates.y += y;
	coordinates.angle += ang;
}
