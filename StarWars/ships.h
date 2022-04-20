#ifndef __CONCRETESHIPS__
#define __CONCRETESHIPS__
#include "SpaceShip.h"

class BomberShip:public SpaceShip
{
public:
	BomberShip();
	BomberShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string type, string color, int x, int y, int angle, int r, Gun* gun) :
		SpaceShip(life, max_guns, dodge_chances, special_attack_chances, type, color, x, y, angle, r, gun) 
	{
		stamina = 100;
	}
	virtual void special_attack(SpaceShip* ship) override;
};

class FighterShip :public SpaceShip
{
public:
	FighterShip();
	FighterShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string type, string color, int x, int y, int angle, int r, Gun* gun) :
		SpaceShip(life, max_guns, dodge_chances, special_attack_chances, type, color, x, y, angle, r, gun) 
	{
		stamina = 300;
	}
	virtual void special_attack(SpaceShip* ship) override;
};

class CruiserShip :public SpaceShip
{
public:
	CruiserShip();
	CruiserShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string type, string color, int x, int y, int angle, int r, Gun* gun) :
		SpaceShip(life, max_guns, dodge_chances, special_attack_chances, type, color, x, y, angle, r, gun) 
	{
		stamina = 200;
	}
	virtual void special_attack(SpaceShip* ship) override;
};
#endif