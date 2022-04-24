#include "Ammunition.h"
Ammunition::Ammunition()
{
	cout << "Ammo" << endl;
}

Ammunition::Ammunition(int damage, int fast, int x, int y, int angle, int w, int h, int target_x, int target_y) :
	damage(damage), fast(fast), coordinates(x, y, angle, w, h), target_x(target_x), target_y(target_y)
{
	int predicted_distance = (int)distance_calculate();
	moveX = -sin(coordinates.angle) * fast;
	moveY = -cos(coordinates.angle) * fast;
}

void Ammunition::subtrack_life()
{
	target->subtract_life(damage);
}

bool Ammunition::check_if_hit()
{
	if ((target_x == coordinates.x) && (target_y == coordinates.y))  // change this condition
	{
		ShipCoordinates current_cord = target->get_coordinates();
		if ((current_cord.x == target_x) && (current_cord.y == target_y))
			return true;
		else
		{
			missed = true;
			return false;
		}
	}
	else if (missed == 1)
		return check_if_hit_after_dodge();
	else
		return false;
}

bool Ammunition::check_if_hit_after_dodge()
{
	return true;
}

void Ammunition::update_position()
{
	coordinates.x += moveX;
	coordinates.y += moveY;
}

int Ammunition::distance_calculate()
{
	return sqrt(pow(target_x - coordinates.x, 2) + pow(target_y - coordinates.y, 2));
}