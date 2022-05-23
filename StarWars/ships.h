#ifndef __CONCRETESHIPS__
#define __CONCRETESHIPS__
#include "SpaceShip.h"
#include "Components.h"

/// <summary>
/// Child class of the SpaceShip class, implementation specific type of the spaceship with overriden virtual methods
/// </summary>
class FighterShip :public SpaceShip
{
private:
	bool increase;
	int dodge_speed;
public:
	FighterShip();
	/// <summary>
	/// Constructor of the FighterShip, it initialize SpaceShip constructor and specific object for this class
	/// </summary>
	/// <param name="life">value of life</param>
	/// <param name="max_guns">max guns which ship can have</param>
	/// <param name="dodge_chances">chances that ship will call defend method (from 0 to 10)</param>
	/// <param name="special_attack_chances">chances that ship will call special_method method (from 0 to 10)</param>
	/// <param name="color">color of the ship (red or blue)</param>
	/// <param name="x">x coordinates of center of the ship</param>
	/// <param name="y">y coordinates of center of the ship</param>
	/// <param name="angle">currnet angle</param>
	/// <param name="r">radious of the ship</param>
	/// <param name="gun">gun</param>
	FighterShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string color, int x, int y, int angle, int r, Gun* gun) :
		SpaceShip(life, max_guns, dodge_chances, special_attack_chances, color, x, y, angle, r, gun)
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
	/// <summary>
	/// method responsible for creating specific object of the ammunition, faster, bigger, causing bigger damages
	/// </summary>
	/// <param name="defender">Pointer at the ship which is defending</param>
	virtual void special_attack(SpaceShip*) override;
	/// <summary>
	/// method responsible for deciding if ship should make dodge
	/// </summary>
	/// <param name="ship">ships which is attacking</param>
	/// <param name="target_x">default x ccordinate of the battle position</param>
	/// <param name="successful_attack">flag which tells us if gun of attacker create Ammunition object</param>
	virtual void defend(SpaceShip* attacker, int target_x, bool succesfull_attack) override;
	/// <summary>
	/// changing attributes that ship is no longer fighting
	/// </summary>
	virtual void after_round() override;
	/// <summary>
	/// method which returns empty Coordinates object created by default constructor, this method should not do enythink
	/// </summary>
	/// <returns>ampty Coordinates object</returns>
	virtual Coordinates get_component_coordinates() override;
	/// <summary>
	/// method created to be compatible with interface
	/// </summary>
	/// <returns>false</returns>
	virtual bool is_component_active() override;
	/// <summary>
	/// method created to be compatible with interface 
	/// </summary>
	/// <returns>pointer at empty Component object</returns>
	virtual Component* get_component() override;
	/// <summary>
	/// method responsible for making dodge, moving ship and finding proper direction of the movement
	/// </summary>
	/// <param name="target_x">battle x coordinates</param>
	void dodge(int target_x);
};

/// <summary>
/// Child class of the SpaceShip class, implementation specific type of the spaceship with overriden virtual methods
/// </summary>
class BomberShip:public SpaceShip
{
private:
	Component* component;
public:
	BomberShip();
	/// <summary>
	/// Constructor of the BomberShip, it initialize SpaceShip constructor and specific object for this class
	/// </summary>
	/// <param name="life">value of life</param>
	/// <param name="max_guns">max guns which ship can have</param>
	/// <param name="dodge_chances">chances that ship will call defend method (from 0 to 10)</param>
	/// <param name="special_attack_chances">chances that ship will call special_method method (from 0 to 10)</param>
	/// <param name="color">color of the ship (red or blue)</param>
	/// <param name="x">x coordinates of center of the ship</param>
	/// <param name="y">y coordinates of center of the ship</param>
	/// <param name="angle">currnet angle</param>
	/// <param name="r">radious of the ship</param>
	/// <param name="gun">gun</param>
	BomberShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string color, int x, int y, int angle, int r, Gun* gun) :
		SpaceShip(life, max_guns, dodge_chances, special_attack_chances, color, x, y, angle, r, gun) 
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
	/// <summary>
	/// method responsible for creating bombs
	/// </summary>
	/// <param name="defender">Pointer at the ship which is defending</param>
	virtual void special_attack(SpaceShip*) override;
	/// <summary>
	/// method which make decision if shield will be created and active
	/// </summary>
	/// <param name="ship">ships which is attacking</param>
	/// <param name="target_x">default x ccordinate of the battle position</param>
	/// <param name="successful_attack">flag which tells us if gun of attacker create Ammunition object</param>
	virtual void defend(SpaceShip* attacker, int target_x, bool succesfull_attack) override;
	/// <summary>
	/// method whic hdisactivate shield
	/// </summary>
	virtual void after_round() override;
	/// <summary>
	/// method responsible for returning coordinates of the shield if it is active
	/// </summary>
	/// <returns>returns Coordinates object</returns>
	virtual Coordinates get_component_coordinates() override;
	/// <summary>
	/// checking if shield is currently active
	/// </summary>
	/// <returns>boolean value</returns>
	virtual bool is_component_active() override;
	/// <summary>
	/// create shield
	/// </summary>
	/// <returns>Pointer of the Component class</returns>
	Component* create_shield();
	void deactivate_shield();
	/// <summary>
	/// method which activate shield and setting its current angle (front to the opponent)
	/// </summary>
	/// <param name="shield_angle">angle calculated between ships</param>
	void activate_shield(double shield_angle);
	/// <summary>
	/// return Pointer of the Component class which is base class of Shield class
	/// </summary>
	/// <returns></returns>
	virtual Component* get_component() override;

};

/// <summary>
/// Child class of the SpaceShip class, implementation specific type of the spaceship with overriden virtual methods
/// </summary>
class CruiserShip :public SpaceShip
{
private:
	Component* component;
	void destroy_ammo_through_laser(Gun*);
public:
	CruiserShip();
	/// <summary>
	/// Constructor of the CruiserShip, it initialize SpaceShip constructor and specific object for this class
	/// </summary>
	/// <param name="life">value of life</param>
	/// <param name="max_guns">max guns which ship can have</param>
	/// <param name="dodge_chances">chances that ship will call defend method (from 0 to 10)</param>
	/// <param name="special_attack_chances">chances that ship will call special_method method (from 0 to 10)</param>
	/// <param name="color">color of the ship (red or blue)</param>
	/// <param name="x">x coordinates of center of the ship</param>
	/// <param name="y">y coordinates of center of the ship</param>
	/// <param name="angle">currnet angle</param>
	/// <param name="r">radious of the ship</param>
	/// <param name="gun">gun</param>
	CruiserShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string color, int x, int y, int angle, int r, Gun* gun) :
		SpaceShip(life, max_guns, dodge_chances, special_attack_chances, color, x, y, angle, r, gun) 
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

	/// <summary>
	/// method responsible for creating laser
	/// </summary>
	/// <param name="defender">Pointer at the ship which is defending</param>
	virtual void special_attack(SpaceShip*) override;
	/// <summary>
	/// method which make decision if laser whic hdestroy all opponents ammo should be created
	/// </summary>
	/// <param name="ship">ships which is attacking</param>
	/// <param name="target_x">default x ccordinate of the battle position</param>
	/// <param name="successful_attack">flag which tells us if gun of attacker create Ammunition object</param>
	virtual void defend(SpaceShip* attacker, int target_x, bool succesfull_attack) override;
	/// <summary>
	/// method responsible for deactivate laser 
	/// </summary>
	virtual void after_round() override;
	/// <summary>
	/// method responsible for returning coordinates of the laser if it is active
	/// </summary>
	/// <returns>returns Coordinates object</returns>
	virtual Coordinates get_component_coordinates() override;
	/// <summary>
	/// checking if laser is currently active
	/// </summary>
	/// <returns>boolean value</returns>
	virtual bool is_component_active() override;
	/// <summary>
	/// create laser
	/// </summary>
	/// <returns>Pointer of the Component class</returns>
	Component* create_laser();
	void deactivate_laser();
	/// <summary>
	/// activate laser
	/// </summary>
	/// <param name="angle">angle of the laser different depends on attacking or defending</param>
	/// <param name="length">length of the laser</param>
	void activate_laser(double angle, int length);
	/// <summary>
	/// method responsible for subtracting life of the oponent
	/// </summary>
	/// <param name="defender">Pointer at the defending ship</param>
	void laser_attack(SpaceShip*);
	/// <summary>
	/// return Pointer of the Component class which is base class of Laser class
	/// </summary>
	/// <returns></returns>
	virtual Component* get_component() override;
};
#endif