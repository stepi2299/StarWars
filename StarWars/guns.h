#ifndef __CONCRETEGUNS__
#define __CONCRETEGUNS__
#include "Gun.h"

class BomberGun :public Gun
{
public:
	BomberGun(string type, int period, int x, int y, int angle, int w, int h) :
		Gun(type, period, x, y, angle, w,  h)
	{
		min_damage = 30;
		fast = 5;
	}
};
class FighterGun :public Gun
{
public:
	FighterGun(string type, int period, int x, int y, int angle, int w, int h) :
		Gun(type, period, x, y, angle, w, h)
	{
		min_damage = 10;
		fast = 1;
	}
};
class CruiserGun :public Gun
{
public:
	CruiserGun(string type, int period, int x, int y, int angle, int w, int h) :
		Gun(type, period, x, y, angle, w, h)
	{
		min_damage = 20;
		fast = 2;
	}
};
#endif