#ifndef __CONCRETEGUNS__
#define __CONCRETEGUNS__
#include "Gun.h"

/// <summary>
/// Class responsible for creating concrete BomberGun which is compatible with BomberShip
/// </summary>
class BomberGun :public Gun
{
public:
	/// <summary>
	/// Contructor of the BomberGun object, initialize Gun constructor and base attributes
	/// </summary>
	/// <param name="period">fPeriod of main loop when gun shoots</param>
	/// <param name="x">x coordinates of the gun (center of the ship)</param>
	/// <param name="y">y coordinates of the gun (center of the ship)</param>
	/// <param name="angle">current gun angle</param>
	/// <param name="w">width of the gun</param>
	/// <param name="h">height of the gun</param>
	/// <param name="color">color of the gun</param>
	/// <param name="r">radious of the gun</param>
	BomberGun(int period, int x, int y, int angle, int w, int h, string color, int r) :
		Gun(period, x, y, angle, w,  h, color, r)
	{
		min_damage = 30;
		fast = 2;
		damage = (rand() % 10) + min_damage;
	}
};

/// <summary>
/// Class responsible for creating concrete FighterGun which is compatible with FighterShip
/// </summary>
class FighterGun :public Gun
{
public:
	/// <summary>
	/// Contructor of the FighterGun object, initialize Gun constructor and base attributes
	/// </summary>
	/// <param name="period">fPeriod of main loop when gun shoots</param>
	/// <param name="x">x coordinates of the gun (center of the ship)</param>
	/// <param name="y">y coordinates of the gun (center of the ship)</param>
	/// <param name="angle">current gun angle</param>
	/// <param name="w">width of the gun</param>
	/// <param name="h">height of the gun</param>
	/// <param name="color">color of the gun</param>
	/// <param name="r">radious of the gun</param>
	FighterGun(int period, int x, int y, int angle, int w, int h, string color, int r) :
		Gun(period, x, y, angle, w, h, color, r)
	{
		min_damage = 10;
		fast = 5;
		damage = (rand() % 10) + min_damage;
	}
};

/// <summary>
/// Class responsible for creating concrete CruiserGun which is compatible with CruiserShip
/// </summary>
class CruiserGun :public Gun
{
public:
	/// <summary>
	/// Contructor of the CruiserGun object, initialize Gun constructor and base attributes
	/// </summary>
	/// <param name="period">fPeriod of main loop when gun shoots</param>
	/// <param name="x">x coordinates of the gun (center of the ship)</param>
	/// <param name="y">y coordinates of the gun (center of the ship)</param>
	/// <param name="angle">current gun angle</param>
	/// <param name="w">width of the gun</param>
	/// <param name="h">height of the gun</param>
	/// <param name="color">color of the gun</param>
	/// <param name="r">radious of the gun</param>
	CruiserGun(int period, int x, int y, int angle, int w, int h, string color, int r) :
		Gun(period, x, y, angle, w, h, color, r)
	{
		min_damage = 20;
		fast = 4;
		damage = (rand() % 10) + min_damage;
	}
};
#endif