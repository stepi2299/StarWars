#ifndef __COMPONENTS__
#define __COMPONENTS__
#include "SpaceShip.h"
#include <SFML/Graphics.hpp>

class SpaceShip;

class Component
{
public:
	virtual bool get_active();
};

class Shield
{
private:
	int stamina, r;
	Coordinates coord;
	sf::Color color;
	bool active;
public:
	Shield();
	Shield(int stamina, sf::Color color, int x, int y, double angle, int w, int h, int r)
		:stamina(stamina), color(color), coord(x, y, angle, w, h), r(r)
	{
		active = false;
	}
	~Shield() {};
	int get_stamina();
	bool get_active();
	void set_active(bool activity);
	void update_coordinates(int x, int y, double ang);
	sf::RectangleShape draw();

};

class Laser
{
private:
	sf::Color color;
	int stamina;
	int damage;
public:
	Laser();
	~Laser() {};
	void attack(SpaceShip* ship);
	void destroy_all_created_ammo(SpaceShip* ship);
};
#endif

