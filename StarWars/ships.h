#ifndef __CONCRETESHIPS__
#define __CONCRETESHIPS__
#include "SpaceShip.h"
#include "Components.h"

class BomberShip:public SpaceShip
{
private:
	Shield shield;
	int defending_round_count;
public:
	BomberShip();
	BomberShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string type, string color, int x, int y, int angle, int r, Gun* gun) :
		SpaceShip(life, max_guns, dodge_chances, special_attack_chances, type, color, x, y, angle, r, gun) 
	{
		stamina = 400;
		defending_round_count = 0;
		shield = create_shield();
	}
	virtual void special_attack(SpaceShip* ship) override;
	virtual void defend(SpaceShip* attacker, int target_x, bool succesfull_attack) override;
	Shield create_shield();
	void deactivate_shield();
	void activate_shield(double shield_angle);
	bool is_shield_active();
	Shield get_shield();
};

class FighterShip :public SpaceShip
{
private:
	bool increase;
	int dodge_speed;
public:
	FighterShip();
	FighterShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string type, string color, int x, int y, int angle, int r, Gun* gun) :
		SpaceShip(life, max_guns, dodge_chances, special_attack_chances, type, color, x, y, angle, r, gun) 
	{
		stamina = 900;
		dodge_speed = 3;
		increase = 0;
	}
	virtual void special_attack(SpaceShip* ship) override;
	virtual void defend(SpaceShip* attacker, int target_x, bool succesfull_attack) override;
	void dodge(int target_x);
};

class CruiserShip :public SpaceShip
{
public:
	CruiserShip();
	CruiserShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string type, string color, int x, int y, int angle, int r, Gun* gun) :
		SpaceShip(life, max_guns, dodge_chances, special_attack_chances, type, color, x, y, angle, r, gun) 
	{
		stamina = 600;
	}
	virtual void special_attack(SpaceShip* ship) override;
	virtual void defend(SpaceShip* attacker, int target_x, bool succesfull_attack) override;
};
#endif