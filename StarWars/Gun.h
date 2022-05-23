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

/// <summary>
/// Class responsibe for providing interface of the all types of guns in game and implement common methods
/// </summary>
class Gun
{
private:
	string color;
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
	/// <summary>
	/// Contructor of the Gun object, initialize base attributes
	/// </summary>
	/// <param name="period">fPeriod of main loop when gun shoots</param>
	/// <param name="x">x coordinates of the gun (center of the ship)</param>
	/// <param name="y">y coordinates of the gun (center of the ship)</param>
	/// <param name="angle">current gun angle</param>
	/// <param name="w">width of the gun</param>
	/// <param name="h">height of the gun</param>
	/// <param name="color">color of the gun</param>
	/// <param name="r">radious of the gun</param>
	Gun(int period, int x, int y, int angle, int w, int h, string color, int r);
	vector <Ammunition*> magazine;
	/// <summary>
	/// method which create ammunition object if loop count is equal period of the gun
	/// </summary>
	/// <param name="ship">pointer at the defending ship</param>
	/// <returns>boolean value when ammo is created</returns>
	bool attack(SpaceShip* ship);
	/// <summary>
	/// method responsible for setting rotation direction during movement
	/// </summary>
	void rotate();
	/// <summary>
	/// method responsible for setting gun rotation during fight
	/// </summary>
	/// <param name="angle">difference between current angle and default angle</param>
	void set_rotation(double ang);
	/// <summary>
	/// updating current angle as angle between gun and center of defender at beginning of the fight
	/// </summary>
	/// <param name="b_angle">angle between gun  and center of defender</param>
	void set_battle_position(double b_angle);
	/// <summary>
	/// getting coordinates of the gun
	/// </summary>
	/// <returns>Coordinates of the ship</returns>
	Coordinates get_coordinates();
	/// <summary>
	/// method responsible for update coordinates of the gun according to methods responsible for setting movement direction and rotation
	/// </summary>
	void update_coord_gun();
	/// <summary>
	/// getter of privvate attribute is_rotating
	/// </summary>
	/// <returns>boolean value if gun is rotating</returns>
	bool is_rotate();
	/// <summary>
	/// method which returns angle which was calculated after defender dodge
	/// </summary>
	/// <returns>angle between gun and center of the ship after dodging</returns>
	double get_diff_ang();  // function which returns angle which was calculated after defender dodge
	/// <summary>
	/// method responsible for setting direction of movement
	/// <param name="x">target coordinates x</param>
	/// <param name="y"> target coordinates y</param>
	/// <param name="tmp_ang">spped of the movement</param>
	/// </summary>
	void move(int x, int y, double tmp_ang);
	/// <summary>
	/// method responsible for setting gun rotation into battle angle (close to default with small diff between gun and center of defender)
	/// </summary>
	void base();
	/// <summary>
	/// method responsible for returning radious of the ship which has this gun
	/// </summary>
	/// <returns>radious of the ship</returns>
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
	/// <summary>
	/// GUI method responsible for drawing gun on the screen
	/// </summary>
	/// <returns>GUI Rectange shaped object</returns>
	sf::RectangleShape draw();
};
#endif

