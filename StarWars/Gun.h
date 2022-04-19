#ifndef __Guns__
#define __Guns__

#include <iostream>
#include "Ammunition.h"
#include "Coordinates.h"
#include <SFML/Graphics.hpp>

using namespace std;

class SpaceShip;
class Ammunition;

class Gun
{
private:
	string type, color;
	int period, r;
	Coordinates coordinates;
	sf::Color sf_color;

protected:
	int min_damage;
	int fast;
	int damage;
public:
	Gun();
	Gun(string type, int period, int x, int y, int angle, int w, int h, string color, int r);
	Ammunition attack(SpaceShip* ship);
	void move(int x, int y);
	string get_type();
	Coordinates get_coordinates();
	~Gun() {}
	sf::RectangleShape draw();
};
#endif

