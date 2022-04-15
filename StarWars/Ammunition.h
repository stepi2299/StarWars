#ifndef __Ammo__
#define __Ammo__
#include "SpaceShip.h"
#include "Coordinates.h"
#include <math.h>

using namespace std;

class SpaceShip;

class Ammunition
{
private:
	int damage, fast, target_x, target_y, predicted_distance;
	int distance = 0;
	Coordinates coordinates;
	SpaceShip* target;
	void subtrack_life();
public:
	Ammunition();
	Ammunition(int damage, int fast, int x, int y, int angle, int w, int h, int target_x, int target_y);
	bool check_if_hit();
	bool check_if_hit_after_dodge();
	void move(int x, int y);
	~Ammunition() {}
};
#endif

