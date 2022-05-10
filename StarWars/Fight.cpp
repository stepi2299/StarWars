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
	blueship->after_round();
	redship->after_round();
	if (turn == "red")
		turn = "blue";
	else
		turn = "red";
}

bool Fight::fighting(SpaceShip* defender, SpaceShip* attacker)
{
	bool successful_attack;
	if (attacker->stamina <= loop_count)
	{
		for (auto i = attacker->armory.begin(); i < attacker->armory.end(); i++)
		{
			if ((*i)->is_rotate() == 1)
			{
				(*i)->rotate();  // jesli atakuj¹cy wykonuje rotacjê to mo¿e ja skoñczyæ przed zaczêciem obrony
				return false;
			}
		}
		if (defender->is_avoiding == 0)
		{
			switch_turn();
			loop_count = 0;
		}
		else
		{
			defender->defend(attacker, target_x, false);  // po wyczerpaniu wytrzyma³oœci atakuj¹cego jesli zacz¹c wykonywaæ unik to go skoñczy zanim zacznie atakowaæ
			return false;
		}
	}
	for (auto i = attacker->armory.begin(); i < attacker->armory.end(); i++)
	{
		successful_attack = (*i)->attack(defender);
		if ((defender->is_avoiding == 0) and (*i)->is_rotate() == 0)
		{
			double calc_angle = calculate_angle(defender, *i);
			if (calc_angle == 0)
				(*i)->base();
			else if ((int)calc_angle != (int)(*i)->get_diff_ang())
				(*i)->set_rotation(calc_angle);
		}
		else if ((*i)->is_rotate() == 1)
			(*i)->rotate();
		defender->defend(attacker, target_x, successful_attack);
	}
	attacker->special_attack(defender);
	return true;
}

void Fight::choosing_fighters()
{
	loop_count++;
	bool test;
	if (turn == "red")
	{
		test = fighting(blueship, redship);
		if_fight_ends(blueship, redship);
	}
	else
	{
		test = fighting(redship, blueship);
		if_fight_ends(redship, blueship);
	}
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
	if (on_place == 1)
	{
		on_place = true;
		return true;
	}
	if ((blueship->coordinates.x == target_x) && (redship->coordinates.x == target_x) && (blueship->coordinates.y == blue_target_y) && (redship->coordinates.y == red_target_y))
	{
		battle_position();
		on_place = true;
		return true;
	}
	else
		return false;
}

double Fight::calculate_angle(SpaceShip* defender, Gun* attacker)
{
	Coordinates coord_gun = attacker->get_coordinates();
	ShipCoordinates coord_ship = defender->get_coordinates();
	int gun_x;
	if (coord_gun.get_def_angl() == 0)
		gun_x = coord_gun.x + attacker->get_ship_r() + coord_gun.w;
	else
		gun_x = coord_gun.x - attacker->get_ship_r() - coord_gun.w;
	if (coord_ship.x - gun_x == 0)
		return 0;
	a = (coord_ship.y - coord_gun.y) / (coord_ship.x - gun_x);
	double alpha =  90.0 - Gun::rad_into_degrees(atan(abs(a)));
	if (((gun_x < coord_ship.x)&&(coord_gun.y > coord_ship.y)) || ((gun_x > coord_ship.x) && (coord_gun.y < coord_ship.y)))
		return alpha;
	else
		return -alpha;
}


void Fight::battle_position()
{
	for (auto i = redship->armory.begin(); i < redship->armory.end(); i++)
		(*i)->set_battle_position(calculate_correct_angle(blueship, (*i)));
	for (auto i = blueship->armory.begin(); i < blueship->armory.end(); i++)
		(*i)->set_battle_position(calculate_correct_angle(redship, (*i)));
}

double Fight::calculate_correct_angle(SpaceShip* defender, Gun* attacker)
{
	ShipCoordinates ship_coord = defender->get_coordinates();
	Coordinates gun_coord = attacker->get_coordinates();
	int gun_x;
	if (gun_coord.get_def_angl() == 0)
		gun_x = gun_coord.x + attacker->get_ship_r() + gun_coord.w;
	else
		gun_x = gun_coord.x - attacker->get_ship_r() - gun_coord.w;
	a = (ship_coord.y - gun_coord.y) / (ship_coord.x - gun_x);
	return 90.0 - Gun::rad_into_degrees(atan(abs(a)));
}

void Fight::move_all_ammo()
{
	bool if_hit;
	for (auto bomb = redship->special_magazine.begin(); bomb < redship->special_magazine.end(); bomb++)
	{
		if_hit = (*bomb)->check_if_hit();
		if (if_hit == true)
		{
			delete (*bomb);
			redship->special_magazine.erase(bomb);
		}
		(*bomb)->update_position();
	}
	for (auto bomb = blueship->special_magazine.begin(); bomb < blueship->special_magazine.end(); bomb++)
	{
		if_hit = (*bomb)->check_if_hit();
		if (if_hit == true)
		{
			delete (*bomb);
			blueship->special_magazine.erase(bomb);
		}
		(*bomb)->update_position();
	}
	for (auto gun = redship->armory.begin(); gun < redship->armory.end(); gun++)
		for (auto ammo = (*gun)->magazine.begin(); ammo < (*gun)->magazine.end(); ammo++)
		{
			if_hit = (*ammo)->check_if_hit();
			if (if_hit == true)
			{
				delete (*ammo);
				(*gun)->magazine.erase(ammo);
			}
			(*ammo)->update_position();
		}
	for (auto gun = blueship->armory.begin(); gun < blueship->armory.end(); gun++)
		for (auto ammo = (*gun)->magazine.begin(); ammo < (*gun)->magazine.end(); ammo++)
		{
			if_hit = (*ammo)->check_if_hit();
			if (if_hit == true)
			{
				delete (*ammo);
				(*gun)->magazine.erase(ammo);
			}
			(*ammo)->update_position();
		}
}

void Fight::if_fight_ends(SpaceShip* defender, SpaceShip* attacker)
{
	if (defender->get_current_life() <= 0)
	{
		attacker->reset_after_fight();
	}
}

SpaceShip* Fight::get_ship(string side)
{
	if (side == "red")
		return redship;
	else if (side == "blue")
		return blueship;
	else
		cout << "wrong side type, type = " << side << endl;
}