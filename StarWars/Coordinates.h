#ifndef __Coordinates__
#define __Coordinates__
#include <iostream>

using namespace std;

/// <summary>
/// Class responsible for creating Coordinates object of the Rectangle shape
/// </summary>
class Coordinates
{
private:
	double default_angle;
	double battle_angle;
public:
	int x, y, w, h;
	double angle;
	Coordinates();
	/// <summary>
	/// Constructor of the Coordinates, initialize essential attributes
	/// </summary>
	/// <param name="x">current x position at the game</param>
	/// <param name="y">current y position at the game</param>
	/// <param name="angle">current angle at the game</param>
	/// <param name="w">width of the object</param>
	/// <param name="h">height of the object</param>
	Coordinates(int x, int y, double angle, int w, int h);
	~Coordinates() {}
	/// <summary>
	/// getter of attribute default angle - 0 or 180
	/// </summary>
	/// <returns>default_angle</returns>
	double get_def_angl();
	/// <summary>
	/// method responsible for setting battle angle at the biginning of every duel, depends on radiois of the ships and distance from each other
	/// </summary>
	/// <param name="b_angle">angle between the Gun and its opponent center</param>
	void set_battle_angle(double b_angle);
	/// <summary>
	/// getter of attribute battle_angle
	/// </summary>
	/// <returns>battle_angle</returns>
	double get_battle_angle();
};

/// <summary>
/// Class responsible for creating Coordinates object of the Circle shape
/// </summary>
class ShipCoordinates
{
private:
	int default_angle;
public:
	int x, y, r, angle;
	ShipCoordinates();
	/// <summary>
	/// Constructor of the ShipCoordinates, initialize essential attributes
	/// </summary>
	/// <param name="x">current x position at the game</param>
	/// <param name="y">current y position at the game</param>
	/// <param name="angle">current angle at the game</param>
	/// <param name="r">radious of the ship</param>
	ShipCoordinates(int x, int y, int angle, int r);
	~ShipCoordinates() {}
	/// <summary>
	/// getter of private attribute default_angle
	/// </summary>
	/// <returns>default_angle</returns>
	int get_def_angl();
};

/// <summary>
/// Class responsible for creating Coordinates object of the Rectangle shape with more accurate x and y coordinates for ammunition
/// </summary>
class AmmoCoordinates
{
private:
	double angle;
public:
	int w, h;
	double x, y;
	AmmoCoordinates();
	/// <summary>
	/// Constructor of the AmmoCoordinates, initialize essential attributes
	/// </summary>
	/// <param name="x">current x position at the game</param>
	/// <param name="y">current y position at the game</param>
	/// <param name="angle">current angle at the game</param>
	/// <param name="w">width of the object</param>
	/// <param name="h">height of the object</param>
	AmmoCoordinates(double x, double y, double angle, int w, int h);
	~AmmoCoordinates() {}
	/// <summary>
	/// getter of private attribute default_angle
	/// </summary>
	/// <returns>default_angle</returns>
	double get_def_angl();
};
#endif

