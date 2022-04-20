#include "Fight.h"

Fight::Fight(SpaceShip* redship, SpaceShip* blueship)
{
	int diff_between_ships = 200;
	this->redship = redship;
	this->blueship = blueship;
	who_is_starting();
	loop_count = 0;
	ShipCoordinates red_coord = redship->get_coordinates();
	ShipCoordinates blue_coord = blueship->get_coordinates();
	int x_min, x_max, y_min, y_max;
	if (red_coord.x - blue_coord.x == 0)
	{
		target_angle = 0.0;
		target_x = red_coord.x;
	}
	else
	{
		a = (red_coord.y - blue_coord.y) / (red_coord.x - blue_coord.x);
		target_angle = 90.0 - tan(a);
		x_min = min(blue_coord.x, red_coord.x);
		x_max = max(blue_coord.x, red_coord.x);
		target_x = (x_max - x_min) / 2 + x_min;
	}
	y_min = min(blue_coord.y, red_coord.y);
	y_max = max(blue_coord.y, red_coord.y);
	red_target_y = (y_max - y_min) / 2 + y_min - diff_between_ships / 2;
	blue_target_y = (y_max - y_min) / 2 + y_min + diff_between_ships / 2;
	on_place = false;
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
	attacker->attack(defender);
	attacker->special_attack(defender);
	if((defender->is_dodge() == 1) or defender->is_avoiding == 1)
		defender->dodge(target_x);
	if (attacker->stamina <= loop_count)
	{
		switch_turn();
		loop_count = 0;
	}
		
}

void Fight::choosing_fighters()
{
	loop_count++;
	if (turn == "red")
		fighting(blueship, redship);
	else
		fighting(redship, blueship);
}

void Fight::move_to_fighting_position()
{
	redship->move(target_x, red_target_y);
	redship->rotate();
	blueship->move(target_x, blue_target_y);
	blueship->rotate();
}

bool Fight::get_on_place()
{
	if (((blueship->coordinates.x == target_x) && (redship->coordinates.x == target_x) && (blueship->coordinates.y == blue_target_y) && (redship->coordinates.y == red_target_y)) or (on_place == 1))
	{
		on_place = true;
		return true;
	}
	else
		return false;
}