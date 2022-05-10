#ifndef __Guns__
#define __Guns__

#include <iostream>
#include "Ammunition.h"
#include "Coordinates.h"
#include <SFML/Graphics.hpp>

using namespace std;

class SpaceShip;
class Ammunition;

const double PI = 3.14159;

class Gun
{
private:
	string type, color;
	int period, r, moveX, moveY;
	Coordinates coordinates;  // gun coordinates are the x,y - middle of the ship, angle - current angle, w,h width and height of the gun
	sf::Color sf_color;
	int loop_count;
	bool is_rotating;
	double target_angle, ang, diff_angle;
	const double angle_range = 90;
protected:
	int min_damage;
	int fast;
	int damage;
public:
	Gun();
	Gun(string type, int period, int x, int y, int angle, int w, int h, string color, int r);
	vector <Ammunition*> magazine;
	bool attack(SpaceShip* ship);
	void rotate();
	void set_rotation(double ang);
	void set_battle_position(double b_angle);
	string get_type();
	Coordinates get_coordinates();
	void update_coord_gun();
	bool is_rotate();
	double get_diff_ang();  // function which returns angle which was calculated after defender dodge
	void move(int x, int y, double tmp_ang);
	void base();
	int get_ship_r();
	static double rad_into_degrees(double rad)
	{
		return (rad * 180.0) / PI;
	}
	static double degrees_into_rad(double deg)
	{
		return (deg * PI) / 180.0;
	}
	~Gun() 
	{
		for (auto i = magazine.begin(); i < magazine.end(); i++)
			delete *i;
	}
	sf::RectangleShape draw();
};
#endif

