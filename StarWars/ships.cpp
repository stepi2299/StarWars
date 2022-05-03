#include "ships.h"
void  FighterShip::special_attack(SpaceShip* ship)
{

}

void FighterShip::defend(SpaceShip* attacker, int target_x, bool succesfull_attack)
{
	if (is_avoiding == true)
		dodge(target_x);
	else if (succesfull_attack == 1 and is_defending() == true and is_avoiding == false)
		dodge(target_x);
}

void FighterShip::dodge(int target_x)
{
	if (is_avoiding == false)
	{
		if (target_x == coordinates.x)
			increase = true;
		else
			increase = false;
	}
	if (increase == 1)
	{
		if (coordinates.x == target_x + coordinates.r * 2)
		{
			is_avoiding = false;
		}
		else
		{
			if (coordinates.x - target_x < coordinates.r)
				move(target_x + coordinates.r * 2, coordinates.y, dodge_speed);
			else
				move(target_x + coordinates.r * 2, coordinates.y, 0);
			is_avoiding = true;
		}
	}
	else if (increase == 0)
	{
		if (coordinates.x == target_x)
			is_avoiding = false;
		else
		{
			if (coordinates.x - target_x > coordinates.r)
				move(target_x, coordinates.y, dodge_speed);
			else
				move(target_x, coordinates.y, 0);
			is_avoiding = true;
		}
	}
}

void  BomberShip::special_attack(SpaceShip* ship)
{

}

Shield BomberShip::get_shield()
{
	return shield;
}

void BomberShip::defend(SpaceShip* attacker, int target_x, bool succesfull_attack)
{
	if (is_shield_active() == true)
	{
		if (shield.get_stamina() <= defending_round_count)
		{
			deactivate_shield();
			defending_round_count = 0;
			return;
		}
		defending_round_count++;
	}
	else if (succesfull_attack == 1 and is_defending() == true)
	{
		double shield_ang = coordinates.get_def_angl() + calculate_ships_angle(attacker);
		activate_shield(shield_ang);
	}
}

void BomberShip::deactivate_shield()
{
	shield.set_active(false);
}

void BomberShip::activate_shield(double shield_angle)
{
	shield.update_coordinates(coordinates.x, coordinates.y, shield_angle);
	shield.set_active(true);
}

bool BomberShip::is_shield_active()
{
	return shield.get_active();
}

Shield BomberShip::create_shield()
{
	return Shield(120, sf_color, coordinates.x, coordinates.y, coordinates.angle, coordinates.r*2, coordinates.r/3, coordinates.r);
}

void  CruiserShip::special_attack(SpaceShip* ship)
{

}

void CruiserShip::defend(SpaceShip* attacker, int target_x, bool succesfull_attack)
{

}
