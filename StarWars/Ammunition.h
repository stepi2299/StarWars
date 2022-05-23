#ifndef __Ammo__
#define __Ammo__
#include "SpaceShip.h"
#include <math.h>
#include <SFML/Graphics.hpp>

using namespace std;

class SpaceShip;

/// <summary>
/// Class responsible for creating object of Ammunition
/// 
/// These object are subtracting life from ships after hit
/// </summary>
class Ammunition
{
private:
	bool check_if_hit_after_dodge();
protected:
	int damage, fast, predicted_distance, distance;
	double moveX, moveY;
	AmmoCoordinates coordinates;
	SpaceShip* target;
	/// <summary>
	/// method responsible for subtracting life from target ship if it was hit
	/// </summary>
	void subtrack_life();
	/// <summary>
	/// method responsible forcalculating distance between starting point of the ammunation object and center of the target ship
	/// </summary>
	/// <returns>distance from end of the gun to the center of the target ship</returns>
	int distance_calculate();
	bool missed;
	friend class Gun;
	friend class Laser;
public:
	Ammunition();
	/// <summary>
	/// Constructor of the Ammunition class, initialize object and essential atributes
	/// 
	/// <param name="damage">damage of the ammunition</param>
	/// <param name="fast">fast of the movement</param>
	/// <param name="x">x coordinates of the ammunition (left upper corner)</param>
	/// <param name="y">y coordinates of the ammunition (left upper corner)</param>
	/// <param name="angle">angle of the ammunition (the same like gun when it was created)</param>
	/// <param name="w">width of the ammunition</param>
	/// <param name="h">height of the ammunition</param>
	/// <param name="target">Pointer at Ship which is target of the ammunition object</param>
	/// </summary>
	Ammunition(int damage, int fast, double x, double y, double angle, int w, int h, SpaceShip* target);
	/// <summary>
	/// method responsible for checking if bullet hit the target
	/// </summary>
	/// <returns>true if hit, otherwise false</returns>
	bool check_if_hit();
	/// <summary>
	/// method responsible for updating bullet's coordinates
	/// </summary>
	void update_position();
	/// <summary>
	/// method using GUI features from SFML, drawing ammunition on the screen
	/// </summary>
	/// <returns>GUI Rectange shaped object</returns>
	sf::RectangleShape draw();
	~Ammunition() {}
};
#endif

