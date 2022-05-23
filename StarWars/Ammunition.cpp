#include "Ammunition.h"
Ammunition::Ammunition()
{
	cout << "Ammo" << endl;
}

Ammunition::Ammunition(int damage, int fast, double x, double y, double angle, int w, int h, SpaceShip *target) :
	damage(damage), fast(fast), coordinates(x, y, angle, w, h), target(target)
{
	predicted_distance = (int)distance_calculate();
	moveX = -sin(Gun::degrees_into_rad(coordinates.get_def_angl())) * fast;
	moveY = cos(Gun::degrees_into_rad(coordinates.get_def_angl())) * fast;
	missed = false;
	distance = 0;
}

void Ammunition::subtrack_life()
{
	target->subtract_life(damage);
}

bool Ammunition::check_if_hit()
{
	double bullet_front_x = -sin(Gun::degrees_into_rad(coordinates.get_def_angl())) * coordinates.h + coordinates.x;
	double bullet_front_y = cos(Gun::degrees_into_rad(coordinates.get_def_angl())) * coordinates.h + coordinates.y;
	ShipCoordinates target_coords = target->get_coordinates();
	if (missed == true)
		return check_if_hit_after_dodge();
	else if (target->is_component_active() == true)
	{
		//BomberShip* bomber_target = dynamic_cast<BomberShip*>(target);
		Coordinates shield_coord = target->get_component_coordinates();
		if (distance<predicted_distance - target_coords.r && distance>predicted_distance - (target_coords.r + shield_coord.h))
			return true;
	}

	if ((bullet_front_x < target_coords.x + (double)target_coords.r) && (bullet_front_x > target_coords.x - (double)target_coords.r)
		&& (bullet_front_y < target_coords.y + (double)target_coords.r) && (bullet_front_y > target_coords.y - (double)target_coords.r - 6))
	{
		subtrack_life();
		return true;
	}
	else if (distance > predicted_distance + target_coords.r)
	{
		missed = true;
		return false;
	}
	else
		return false;
}

bool Ammunition::check_if_hit_after_dodge()
{
	if ((coordinates.x < 0) || (coordinates.x > 1900) || (coordinates.y < 0) || (coordinates.y > 1100))
	{
		return true;
	}
	else
		return false;
}

void Ammunition::update_position()
{
	coordinates.x += moveX;
	coordinates.y += moveY;
	distance += fast;
}

int Ammunition::distance_calculate()
{
	return sqrt(pow(target->get_coordinates().x - coordinates.x, 2) + pow(target->get_coordinates().y - coordinates.y, 2));
}

sf::RectangleShape Ammunition::draw()
{
	sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(coordinates.w, coordinates.h));
	//rect.setOrigin()
	rect.setPosition(coordinates.x, coordinates.y);
	rect.setFillColor(sf::Color::Yellow);
	rect.setRotation(coordinates.get_def_angl());
	return rect;
}
