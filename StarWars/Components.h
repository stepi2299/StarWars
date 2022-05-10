#ifndef __COMPONENTS__
#define __COMPONENTS__
#include "SpaceShip.h"
#include <SFML/Graphics.hpp>

class SpaceShip;

class Component
{
private:
	int stamina;
	bool active;
protected:
	Coordinates coord;
	int r;
	sf::Color color;
public:
	Component();
	Component(int stamina, sf::Color color, int x, int y, double angle, int w, int h, int r)
		:stamina(stamina), color(color), coord(x, y, angle, w, h), r(r)
	{
		active = false;
	}
	~Component() {};
	int get_stamina();
	bool get_active();
	void set_active(bool active);
	Coordinates get_coordinates();
	virtual sf::RectangleShape draw();

};
class Shield : public Component
{
public:
	Shield();
	Shield(int stamina, sf::Color color, int x, int y, double angle, int w, int h, int r)
		:Component(stamina, color, x, y, angle, w, h, r)
	{}
	~Shield() {};
	void update_coordinates(int x, int y, double ang);
	sf::RectangleShape draw();

};

class Laser : public Component
{
private:
	int damage;
public:
	Laser();
	Laser(int stamina, int damage, sf::Color color, int x, int y, double angle, int w, int h, int r)
		:Component(stamina, color, x, y, angle, w, h, r), damage(damage)
	{}
	~Laser() {};
	void attack(SpaceShip*);
	void destroy_all_created_ammo(Gun*);
	sf::RectangleShape draw();
	void update_coordinates(int x, int y, double ang, int h);
};
#endif

