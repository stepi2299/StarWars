#include "Components.h"

Component::Component() 
{
	cout << "Default Component" << endl;
	stamina = 100;
	active = false;
	r = 5;
	coord = Coordinates(0, 0, 0, 0, 0);
	color = sf::Color::White;
}

int Component::get_stamina()
{
	return stamina;
}

bool Component::get_active()
{
	return active;
}

void Component::set_active(bool active)
{
	this->active = active;
}

Coordinates Component::get_coordinates()
{
	return coord;
}
sf::RectangleShape Component::draw()
{
	return sf::RectangleShape(sf::Vector2f(1, 1));
}

void Shield::update_coordinates(int x, int y, double ang)
{
	coord.x = x;
	coord.y = y;
	coord.angle = ang;
}

Shield::Shield()
{
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

Laser::Laser()
{
	cout << "Domyslny laser" << endl;
}


void Laser::update_coordinates(int x, int y, double ang, int h)
{
	coord.x = x;
	coord.y = y;
	coord.angle = ang;
	coord.h = h;
}

sf::RectangleShape Laser::draw()
{
	sf::RectangleShape rec = sf::RectangleShape(sf::Vector2f(coord.w, coord.h));
	rec.setOrigin(r/3, -r);
	rec.setPosition(coord.x, coord.y);
	rec.setFillColor(color);
	rec.setRotation((float)coord.angle);
	return rec;
}

void Laser::destroy_all_created_ammo(Gun* gun)
{
	for (auto i = gun->magazine.begin(); i < gun->magazine.end(); i++)
	{
		if ((*i)->missed == false)
		{
			delete (*i);
			gun->magazine.erase(i);
		}
	}
}

void Laser::attack(SpaceShip* defender)
{
	defender->subtract_life(damage);
}