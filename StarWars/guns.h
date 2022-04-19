#ifndef __CONCRETEGUNS__
#define __CONCRETEGUNS__
#include "Gun.h"

class BomberGun :public Gun
{
public:
	BomberGun(string type, int period, int x, int y, int angle, int w, int h, string color, int r) :
		Gun(type, period, x, y, angle, w,  h, color, r)
	{
		min_damage = 30;
		fast = 5;
		damage = (rand() % 10) + min_damage;
	}
};
class FighterGun :public Gun
{
public:
	FighterGun(string type, int period, int x, int y, int angle, int w, int h, string color, int r) :
		Gun(type, period, x, y, angle, w, h, color, r)
	{
		min_damage = 10;
		fast = 1;
		damage = (rand() % 10) + min_damage;
	}
};
class CruiserGun :public Gun
{
public:
	CruiserGun(string type, int period, int x, int y, int angle, int w, int h, string color, int r) :
		Gun(type, period, x, y, angle, w, h, color, r)
	{
		min_damage = 20;
		fast = 2;
		damage = (rand() % 10) + min_damage;
	}
};
#endif