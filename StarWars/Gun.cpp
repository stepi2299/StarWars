#include "Gun.h"
Gun::Gun()
{
	cout << "Gun" << endl;
}

Gun::Gun(string type, int period, int x, int y, int angle, int w, int h, string color, int r):
	type(type), period(period), coordinates(x, y, angle, w, h), color(color), r(r)
{
	if (color == "red")
		sf_color = sf::Color::Red;
	else
		sf_color = sf::Color::Blue;
	loop_count = 0;
}

string Gun::get_type()
{
	return this->type;
}

Coordinates Gun::get_coordinates()
{
	return coordinates;
}

bool Gun::attack(SpaceShip *ship)
{
	if (loop_count == period)
	{
		ShipCoordinates target_coord = ship->get_coordinates();
		//Ammunition* ammo = new Ammunition(damage, fast, coordinates.x + coordinates.w / 3, coordinates.y + coordinates.h, coordinates.angle, coordinates.w / 5, coordinates.h / 5, target_coord.x, target_coord.y);
		//magazine.push_back(ammo);
		loop_count = 0;
		return true;
	}
	loop_count++;
	return false;
}

sf::RectangleShape Gun::draw()
{
	sf::RectangleShape rec = sf::RectangleShape(sf::Vector2f(coordinates.w, coordinates.h));
	rec.setOrigin(-r, 0);
	rec.setPosition(coordinates.x, coordinates.y);
	rec.setFillColor(sf_color);
	rec.setRotation((float)coordinates.angle);
	return rec;
}

void Gun::update_coord_gun()
{
	coordinates.x += moveX;
	coordinates.y += moveY;
	coordinates.angle += ang;

	moveX = 0;
	moveY = 0;
	ang = 0;
}

void Gun::move(int x, int y, double tmp_ang)
{
	moveX = x;
	moveY = y;
	ang = tmp_ang;
}


void Gun::set_rotation(double ang)
{
	if (abs(ang) + abs(coordinates.angle) < angle_range + coordinates.get_def_angl())
	{
		target_angle = coordinates.get_def_angl() + ang;
		diff_angle = ang;
		is_rotating = true;
	}
	else
	{
		cout << "Angle difference is too big: angle= " << target_angle << endl;
		is_rotating = false;
	}
}

bool Gun::is_rotate()
{
	return is_rotating;
}

void Gun::rotate()
{
	double rotation_speed = 2;
	if (is_rotating == true)
	{
		double ang_diff = abs(target_angle - coordinates.angle);
		if (ang_diff <= rotation_speed)
		{
			rotation_speed = ang_diff;
		}
		if ((int)target_angle == (int)coordinates.angle)
		{
			ang = 0;
			is_rotating = false;
			return;
		}
		else if (target_angle - coordinates.angle > 0)
			ang = rotation_speed;
		else if (target_angle - coordinates.angle < 0)
			ang = -rotation_speed;

	}
}

double Gun::get_diff_ang()
{
	return diff_angle;
}

void Gun::base()
{
	target_angle = coordinates.get_battle_angle();
	is_rotating = true;
}

void Gun::set_battle_position(double b_angle)
{
	coordinates.set_battle_angle(b_angle);
	target_angle = coordinates.get_battle_angle();
	coordinates.angle = coordinates.get_battle_angle();
}

int Gun::get_ship_r()
{
	return r;
}