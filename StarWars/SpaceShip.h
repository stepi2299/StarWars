#ifndef __Ships__
#define __Ships__

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
class Shield;

class SpaceShip
{
private:
	int life, max_guns, moveX = 0, moveY = 0, ang = 0;
	int defend_chances, special_attack_chances;
	string type, color;
	bool check_special_attack();
	bool fighting;
	int speed;
protected:
	int stamina;
	friend class Fight;
	bool is_defending();
	bool is_avoiding;
	sf::Color sf_color;
	ShipCoordinates coordinates;

public:
	SpaceShip();
	SpaceShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string type, string color, int x, int y, int angle, int r, Gun *gun);
	vector <Gun*> armory;
	virtual void defend(SpaceShip* ship, int target_x, bool successful_attack) = 0;
	virtual void special_attack(SpaceShip* ship) = 0;
	void take_gun(Gun *g);
	void drop_the_gun();
	bool can_take_gun(Gun *g);
	void attack(SpaceShip* ship);
	ShipCoordinates get_coordinates();
	void move(int x, int y, int current_speed=0);
	void update_position();
	void rotate();
	SpaceShip find_oponent();  // rethink about if none is found
	int get_current_life();
	void subtract_life(int damage);
	void destroy();
	sf::CircleShape draw();
	void set_fighting(bool fight);
	bool get_fighting();
	float get_distance_between_ships(SpaceShip* ship);
	void reset_after_fight();
	void base();
	bool is_shield_active();
	string get_type();
	virtual Shield get_shield();
	double calculate_ships_angle(SpaceShip* ship);
	~SpaceShip() 
	{
		for (auto i = armory.begin(); i < armory.end(); i++)
			delete* i;
	}
};
#endif
