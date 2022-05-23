#ifndef __SPACESHIP__
#define __SPACESHIP__

#include <vector>
#include "Coordinates.h"
#include "Gun.h"
#include <cstring>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Fight.h"
#include "Components.h"

using namespace std;

class Gun;
class Component;
class Ammunition;

/// <summary>
/// Class providing interface for ships objects and implementation of the common methods used by all child classes
/// 
/// The most important class during the game, provide interface for all ships in game
/// </summary>
class SpaceShip
{
private:
	int life, max_guns, moveX = 0, moveY = 0, ang = 0;
	int defend_chances, special_attack_chances;
	string color;
	bool fighting;
	int speed;
protected:
	int stamina, active_round;
	friend class Fight;
	/// <summary>
	/// method responsible for deciding if object will defend agains attacker ship
	/// </summary>
	/// <returns>boolean value</returns>
	bool is_defending();
	/// <summary>
	/// method responsible for deciding if object will use special attack agains defending ship
	/// </summary>
	/// <returns>boolean value</returns>
	bool is_special_attack();
	bool is_avoiding;
	sf::Color sf_color;
	ShipCoordinates coordinates;

public:
	SpaceShip();
	/// <summary>
	/// Constructor of the SpaceShip
	/// </summary>
	/// <param name="life">life of the ship</param>
	/// <param name="max_guns">max guns which ship can have</param>
	/// <param name="dodge_chances">chances that ship will call defend method (from 0 to 10)</param>
	/// <param name="special_attack_chances">chances that ship will call special_method method (from 0 to 10)</param>
	/// <param name="color">color of the ship (red or blue)</param>
	/// <param name="x">x coordinates of center of the ship</param>
	/// <param name="y">y coordinates of center of the ship</param>
	/// <param name="angle">currnet angle</param>
	/// <param name="r">radoious of the ship</param>
	/// <param name="gun">gun</param>
	SpaceShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string color, int x, int y, int angle, int r, Gun *gun);
	vector <Gun*> armory;
	vector <Ammunition*> special_magazine;
	/// <summary>
	/// virtual method responsible for defending, implement in child class
	/// </summary>
	/// <param name="ship">ships which is attacking</param>
	/// <param name="target_x">default x ccordinate of the battle position</param>
	/// <param name="successful_attack">flag which tells us if gun of attacker create Ammunition object</param>
	virtual void defend(SpaceShip* ship, int target_x, bool successful_attack) = 0;
	/// <summary>
	/// virtual method responsible fo special attack, implement in child class
	/// </summary>
	/// <param name="">ships which is defending</param>
	virtual void special_attack(SpaceShip*) = 0;
	/// <summary>
	/// virtual method responsible for making set of action after round of attacking or defending, implement in child method
	/// </summary>
	virtual void after_round() = 0;
	/// <summary>
	/// virtual method responsible for returning coordinates of Coomponent, implement in child method
	/// </summary>
	/// <returns>current coordinates of the component (Shield or Laser)</returns>
	virtual Coordinates get_component_coordinates() = 0;
	/// <summary>
	/// virtual method responsible for returning if component for specific type of ship is active, implement in child method
	/// </summary>
	/// <returns>true if component (shield or laser) is active, otherwise false</returns>
	virtual bool is_component_active() = 0;
	/// <summary>
	/// virtual method responsible for returning pointer of the Component, implement in child method
	/// </summary>
	/// <returns>Pointer at the Component (Shield or Laser)</returns>
	virtual Component* get_component() = 0;
	/// <summary>
	/// method responsible for adding gun to vector which stores guns for specific ship
	/// </summary>
	/// <param name="gun"></param>
	void take_gun(Gun *g);
	/// <summary>
	/// remobing gun from vector which stores ship guns
	/// </summary>
	void drop_the_gun();
	/// <summary>
	/// method responsible for checking if specific ships can take specific gun
	/// </summary>
	/// <param name="guyn">Pointer at the gun which we want to take</param>
	/// <returns>true if types of the ships and gun are similar, otherwise false</returns>
	bool can_take_gun(Gun *g);
	/// <summary>
	/// method responsible for returning current coordinates of the ships
	/// </summary>
	/// <returns>current cordinates of the ship</returns>
	ShipCoordinates get_coordinates();
	/// <summary>
	/// method responsible for setting direction of the movement
	/// </summary>
	/// <param name="x">target coordinates x</param>
	/// <param name="y"> target coordinates y</param>
	/// <param name="current_speed">spped of the movement</param>
	void move(int x, int y, int current_speed=0);
	/// <summary>
	/// method responsible for updating coordinates of the ship and guns, depends on several methods responsible for setting direction movement
	/// </summary>
	void update_position();
	/// <summary>
	/// method responsible for setting direction of the movement
	/// </summary>
	void rotate();
	/// <summary>
	/// getter of ship life
	/// </summary>
	/// <returns>private attribute life</returns>
	int get_current_life();
	/// <summary>
	/// method responsible for subtracting life of the ship, called from Ammunation objects which will hit into ship
	/// </summary>
	/// <param name="damage">value of losing life</param>
	void subtract_life(int damage);
	/// <summary>
	/// GUI method responsible for drawing ship on the screen
	/// </summary>
	/// <returns>GUI Circle shaped object</returns>
	sf::CircleShape draw();
	/// <summary>
	/// setting attribute fighting if this ship became one of the creator of the Fight object
	/// </summary>
	/// <param name="fight"> boolean value setting when ship will find opponent</param>
	void set_fighting(bool fight);
	/// <summary>
	/// getter method for attribute fighting
	/// </summary>
	/// <returns>boolean attribute fighting</returns>
	bool get_fighting();
	/// <summary>
	/// getter for attribute which tells us distance from fighting ships
	/// </summary>
	/// <param name="ship"></param>
	/// <returns></returns>
	float get_distance_between_ships(SpaceShip* ship);
	/// <summary>
	/// method responsible for cleaning after fight, like deleting unnecessary objects like Ammunition objects etc. and setting proper attributes again
	/// </summary>
	void reset_after_fight();
	/// <summary>
	/// method called after fights, setting current angle as default one (angle setting when object was created (190 or 0 degrees)
	/// </summary>
	void base();
	/// <summary>
	/// method responsible for calculating angle between centers of two ships
	/// </summary>
	/// <param name="ship">Pointer of the ship with which we are fighting</param>
	/// <returns>angle between centers of the ships</returns>
	double calculate_ships_angle(SpaceShip* ship);
	~SpaceShip() 
	{
		for (auto i = armory.begin(); i < armory.end(); i++)
			delete* i;
		armory.clear();
		for (auto i = special_magazine.begin(); i < special_magazine.end(); i++)
			delete* i;
		special_magazine.clear();
	}
};
#endif
