#ifndef __CONCRETESHIPS__
#define __CONCRETESHIPS__
#include "SpaceShip.h"
#include "Components.h"


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
	~FighterShip()
	{
		for (auto i = armory.begin(); i < armory.end(); i++)
			delete* i;
		for (auto i = special_magazine.begin(); i < special_magazine.end(); i++)
			delete* i;
	}
	virtual void special_attack(SpaceShip*) override;
	virtual void defend(SpaceShip* attacker, int target_x, bool succesfull_attack) override;
	virtual void after_round() override;
	virtual Coordinates get_component_coordinates() override;
	virtual bool is_component_active() override;
	virtual Component* get_component() override;
	void dodge(int target_x);
};


class BomberShip:public SpaceShip
{
private:
	Component* component;
public:
	BomberShip();
	BomberShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string type, string color, int x, int y, int angle, int r, Gun* gun) :
		SpaceShip(life, max_guns, dodge_chances, special_attack_chances, type, color, x, y, angle, r, gun) 
	{
		stamina = 500;
		component = create_shield();
	}
	~BomberShip()
	{
		for (auto i = armory.begin(); i < armory.end(); i++)
			delete* i;
		for (auto i = special_magazine.begin(); i < special_magazine.end(); i++)
			delete* i;
		delete component;
	}
	virtual void special_attack(SpaceShip*) override;
	virtual void defend(SpaceShip* attacker, int target_x, bool succesfull_attack) override;
	virtual void after_round() override;
	virtual Coordinates get_component_coordinates() override;
	virtual bool is_component_active() override;
	Component* create_shield();
	void deactivate_shield();
	void activate_shield(double shield_angle);
	virtual Component* get_component() override;

};

class CruiserShip :public SpaceShip
{
private:
	Component* component;
	void destroy_ammo_through_laser(Gun*);
public:
	CruiserShip();
	CruiserShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string type, string color, int x, int y, int angle, int r, Gun* gun) :
		SpaceShip(life, max_guns, dodge_chances, special_attack_chances, type, color, x, y, angle, r, gun) 
	{
		stamina = 700;
		component = create_laser();
	}
	~CruiserShip()
	{
		for (auto i = armory.begin(); i < armory.end(); i++)
			delete* i;
		for (auto i = special_magazine.begin(); i < special_magazine.end(); i++)
			delete* i;
		delete component;
	}
	virtual void special_attack(SpaceShip*) override;
	virtual void defend(SpaceShip* attacker, int target_x, bool succesfull_attack) override;
	virtual void after_round() override;
	virtual Coordinates get_component_coordinates() override;
	virtual bool is_component_active() override;
	Component* create_laser();
	void deactivate_laser();
	void activate_laser(double angle, int length);
	void laser_attack(SpaceShip*);
	virtual Component* get_component() override;
};
#endif