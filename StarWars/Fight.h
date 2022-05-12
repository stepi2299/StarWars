#ifndef __FIGHT__
#define __FIGHT__

#include "SpaceShip.h"
#include <math.h>
class SpaceShip;
class Gun;

class Fight
{
private:
	SpaceShip * redship, * blueship;
	string turn;
	void who_is_starting();
	void switch_turn();
	int loop_count;
	int target_x, red_target_y, blue_target_y;
	double a, target_angle, angle_correction;
	double calculate_angle(SpaceShip* defender, Gun* attacker);
	void fighting(SpaceShip* defender, SpaceShip* attacker);
public:
	bool on_place;
	Fight(SpaceShip *redship, SpaceShip *blueship);
	void choosing_fighters();
	void move_to_fighting_position();
	bool get_on_place();
	void battle_position();
	double calculate_correct_angle(SpaceShip* defender, Gun* attacker);
	void move_all_ammo();
	SpaceShip* get_ship(string);
	void destroy_waste_after_fight();
	~Fight() 
	{
		destroy_waste_after_fight();
	}
};
#endif
