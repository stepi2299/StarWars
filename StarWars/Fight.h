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
public:
	Fight(SpaceShip *redship, SpaceShip *blueship);
	void fighting(SpaceShip* defender, SpaceShip* attacker);
	void choosing_fighters();
};
#endif
