#ifndef __Ammo__
#define __Ammo__
#include "SpaceShip.h"
#include "Coordinates.h"
#include <math.h>
#include <SFML/Graphics.hpp>

using namespace std;

class SpaceShip;

class Ammunition
{
private:
	int damage, fast, predicted_distance, distance;
	double moveX, moveY;
	AmmoCoordinates coordinates;
	SpaceShip* target;
	void subtrack_life();
	int distance_calculate();
	bool missed;
	friend class Gun;
public:
	Ammunition();
	Ammunition(int damage, int fast, double x, double y, double angle, int w, int h, SpaceShip* target);
	bool check_if_hit();
	bool check_if_hit_after_dodge();
	void update_position();
	sf::RectangleShape draw();
	~Ammunition() {}
};
#endif

