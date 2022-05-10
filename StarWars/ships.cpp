#include "ships.h"
void  FighterShip::special_attack(SpaceShip* defender)
{
	if (is_special_attack() == true)
	{
		ShipCoordinates def_coords = defender->get_coordinates();
		double shot_angle = calculate_ships_angle(defender) + coordinates.get_def_angl();
		Ammunition* ammo = new Ammunition(60, 6, coordinates.x - sin(Gun::degrees_into_rad(def_coords.angle)) * def_coords.r,
			coordinates.y - cos(Gun::degrees_into_rad(def_coords.angle)) * def_coords.r,
			shot_angle, 4, 20, defender);
		special_magazine.push_back(ammo);
	}
}

void FighterShip::defend(SpaceShip* attacker, int target_x, bool succesfull_attack)
{
	if (is_avoiding == true)
		dodge(target_x);
	else if (succesfull_attack == 1 and is_defending() == true and is_avoiding == false)
		dodge(target_x);
}

void FighterShip::after_round()
{
	is_avoiding = false;
}

bool FighterShip::is_component_active()
{
	return false;
}

Coordinates FighterShip::get_component_coordinates()
{
	cout << "Sth went wrong, it should not be call out" << endl;
	return Coordinates();
}

Component* FighterShip::get_component()
{
	cout << "Sth went wrong, it should not be call out" << endl;
	Component* comp = new Component();
	return comp;
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

void BomberShip::after_round()
{
	if (is_component_active() == true)
		deactivate_shield();
	active_round=0;
}

void  BomberShip::special_attack(SpaceShip* defender)
{
	if (is_special_attack() == true)
	{
		ShipCoordinates def_coords = defender->get_coordinates();
		double bomb_ang = calculate_ships_angle(defender) + coordinates.get_def_angl();
		int sqare_side = 15;
		Ammunition* ammo = new Ammunition(100, 1, coordinates.x - sin(Gun::degrees_into_rad(def_coords.angle)) * def_coords.r,
			coordinates.y - cos(Gun::degrees_into_rad(def_coords.angle)) * def_coords.r,
			bomb_ang, sqare_side, sqare_side, defender);
		special_magazine.push_back(ammo);
	}
}

Component* BomberShip::get_component()
{
	return component;
}

void BomberShip::defend(SpaceShip* attacker, int target_x, bool succesfull_attack)
{
	if (is_component_active() == true)
	{
		if (component->get_stamina() <= active_round)
		{
			deactivate_shield();
			active_round = 0;
			return;
		}
		active_round++;
	}
	else if (succesfull_attack == 1 and is_defending() == true)
	{
		double shield_ang = coordinates.get_def_angl() + calculate_ships_angle(attacker);
		activate_shield(shield_ang);
	}
}

void BomberShip::deactivate_shield()
{
	component->set_active(false);
}

void BomberShip::activate_shield(double shield_angle)
{
	Shield* bomb_component = dynamic_cast<Shield*>(component);
	bomb_component->update_coordinates(coordinates.x, coordinates.y, shield_angle);
	bomb_component->set_active(true);
}

bool BomberShip::is_component_active()
{
	return component->get_active();
}

Component* BomberShip::create_shield()
{
	Component* comp = new Shield(200, sf_color, coordinates.x, coordinates.y, coordinates.angle, coordinates.r*2, coordinates.r/2, coordinates.r);
	return comp;
}

Coordinates BomberShip::get_component_coordinates()
{
	return component->get_coordinates();
}

void  CruiserShip::special_attack(SpaceShip* defender)
{
	if (is_component_active() == true)
	{
		if (component->get_stamina() <= active_round)
		{
			deactivate_laser();
			active_round = 0;
			return;
		}
		laser_attack(defender);
		active_round++;

	}
	else if (is_special_attack() == true)
	{
		ShipCoordinates def_coords = defender->get_coordinates();
		double laser_ang = calculate_ships_angle(defender) + coordinates.get_def_angl();
		int laser_length = (int)(sqrt(pow(def_coords.x - coordinates.x, 2) + pow(def_coords.y - coordinates.y, 2)) - (coordinates.r + def_coords.r));
		activate_laser(laser_ang, laser_length);
		laser_attack(defender);
	}
}

void CruiserShip::laser_attack(SpaceShip* defender)
{
	Laser* laser_component = dynamic_cast<Laser*>(component);
	laser_component->attack(defender);
}

void CruiserShip::defend(SpaceShip* attacker, int target_x, bool succesfull_attack)
{
	if (is_component_active() == true)
	{
		if (component->get_stamina() <= active_round)
		{
			deactivate_laser();
			active_round = 0;
			return;
		}
		destroy_ammo_through_laser(attacker->armory[0]);
		active_round++;
		
	}
	else if (succesfull_attack == 1 and is_defending() == true)
	{
		Coordinates gun_coord = attacker->armory[0]->get_coordinates();
		int gun_ship_r = attacker->armory[0]->get_ship_r();
		double laser_ang = gun_coord.angle + 180.0;
		int laser_length = (int)(sqrt(pow((gun_coord.x-sin(Gun::degrees_into_rad(gun_coord.angle))*gun_ship_r) - coordinates.x, 2) 
			+ pow((gun_coord.y+cos(Gun::degrees_into_rad(gun_coord.angle)) * gun_ship_r) - coordinates.y, 2)) - coordinates.r - gun_coord.h/4);
		activate_laser(laser_ang, laser_length);
		destroy_ammo_through_laser(attacker->armory[0]);
	}
}

void CruiserShip::after_round()
{
	if (is_component_active() == true)
		component->set_active(false);
	active_round=0;
}

Coordinates CruiserShip::get_component_coordinates()
{
	return component->get_coordinates();
}

bool CruiserShip::is_component_active()
{
	return component->get_active();
}

Component* CruiserShip::create_laser()
{
	Component* comp = new Laser(50, 2, sf_color, coordinates.x, coordinates.y, coordinates.angle, coordinates.r / 3, 10, coordinates.r);
	return comp;
}

void CruiserShip::activate_laser(double angle, int length)
{
	Laser* laser_component = dynamic_cast<Laser*>(component);
	laser_component->update_coordinates(coordinates.x, coordinates.y, angle, length);
	laser_component->set_active(true);
}

void CruiserShip::deactivate_laser()
{
	component->set_active(false);
}

Component* CruiserShip::get_component()
{
	return component;
}

void CruiserShip::destroy_ammo_through_laser(Gun* gun)
{
	Laser* laser_component = dynamic_cast<Laser*>(component);
	laser_component->destroy_all_created_ammo(gun);
}
