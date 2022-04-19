#ifndef __FIGHT__
#define __FIGHT__

#include "SpaceShip.h"
class SpaceShip;

class Fight
{
private:
	SpaceShip * redship, * blueship;
	string turn;
	void who_is_starting();
	void switch_turn();
	int loop_count;
	int target_x, red_target_y, blue_target_y;
	float a, target_angle;
public:
	Fight(SpaceShip *redship, SpaceShip *blueship);
	void fighting(SpaceShip* defender, SpaceShip* attacker);
	void choosing_fighters();
	void move_to_fighting_position();
};
#endif
