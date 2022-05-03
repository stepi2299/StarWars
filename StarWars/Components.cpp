#include "Components.h"

bool Component::get_active()
{
	return false;
}

int Shield::get_stamina()
{
	return stamina;
}

Shield::Shield()
{
}

bool Shield::get_active()
{
	return active;
}

void Shield::set_active(bool activate)
{
	active = activate;
}

void Shield::update_coordinates(int x, int y, double ang)
{
	coord.x = x;
	coord.y = y;
	coord.angle = ang;
}

sf::RectangleShape Shield::draw()
{
	sf::RectangleShape rec = sf::RectangleShape(sf::Vector2f(coord.w, coord.h));
	rec.setOrigin(r, -r);
	rec.setPosition(coord.x, coord.y);
	rec.setFillColor(color);
	rec.setRotation((float)coord.angle);
	return rec;
}
