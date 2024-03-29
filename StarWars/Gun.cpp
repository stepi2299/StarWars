#include "Gun.h"
Gun::Gun()
{
	cout << "Gun" << endl;
}

Gun::Gun(int period, int x, int y, int angle, int w, int h, string color, int r):
	period(period), coordinates(x, y, angle, w, h), color(color), r(r)
{
	if (color == "red")
		sf_color = sf::Color::Red;
	else
		sf_color = sf::Color::Blue;
	loop_count = 0;
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
		double ammo_x, ammo_y, ammo_angle;
		int ammo_w, ammo_h;
		double h1 = sin(degrees_into_rad(coordinates.angle)) * (r + coordinates.w / 3);  // r�nica wysoko�ci mi�dzy �rodkiem staku, a pocz�tkiem broni
		double h2 = cos(degrees_into_rad(coordinates.angle)) * coordinates.h; // r�nica wysoko�ci mi�dzy pocz�tkiem borni a ko�cem broni
		double w1 = cos(degrees_into_rad(coordinates.angle)) * (r + coordinates.w / 3);  // r�nica w szeroko�ci mi�dzy �rodkiem statku a ko�cem broni
		double w2 = - sin(degrees_into_rad(coordinates.angle)) * coordinates.h; // r�nica szeroko�ci mi�dzy pocz�tkiem borni a ko�cem broni
		ammo_x = coordinates.x + w1 + w2;
		ammo_y = coordinates.y + h1 + h2;
		ammo_w = coordinates.w / 3;
		ammo_h = coordinates.h / 3;
		ammo_angle = coordinates.angle;
		Ammunition* ammo = new Ammunition(damage, fast, ammo_x, ammo_y, ammo_angle, ammo_w, ammo_h, ship);
		magazine.push_back(ammo);
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
	double correction_angle=0;
	if (abs(ang) < angle_range )
	{
		if (ang > 0)
			correction_angle = 0.3 * ang;
		ang = ang - correction_angle;
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