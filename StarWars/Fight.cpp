#include "Fight.h"

Fight::Fight(SpaceShip* redship, SpaceShip* blueship)
{
	this->redship = redship;
	this->blueship = blueship;
	who_is_starting();
	loop_count = 0;
}
void Fight::who_is_starting()
{
	int rd = (rand() % 2) + 1;
	if (rd == 1)
		turn = "red";
	else
		turn = "blue";
}

void Fight::switch_turn()
{
	if (turn == "red")
		turn = "blue";
	else
		turn = "red";
}

void Fight::fighting(SpaceShip* defender, SpaceShip* attacker)
{
	defender->dodge();
	attacker->attack(defender);
	attacker->special_attack(defender);
	if (attacker->stamina >= loop_count)
		switch_turn();
}

void Fight::choosing_fighters()
{
	loop_count++;
	if (turn == "red")
		fighting(blueship, redship);
	else
		fighting(redship, blueship);
}


