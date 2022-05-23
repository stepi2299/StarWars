#ifndef __COMPONENTS__
#define __COMPONENTS__
#include "SpaceShip.h"
#include <SFML/Graphics.hpp>

class SpaceShip;

/// <summary>
/// Class providing interface for concrete components like shield and laser and implementation of common methods
/// </summary>
class Component
{
private:
	int stamina;
	bool active;
protected:
	Coordinates coord;
	int r;
	sf::Color color;
public:
	Component();
	/// <summary>
	/// Constructor of the Component class, initialize essential attributes
	/// </summary>
	/// <param name="stamina">how many loop count component will be active</param>
	/// <param name="color">red or blue</param>
	/// <param name="x">x component coordinates(left upper corner)</param>
	/// <param name="y">y component coordinates(left upper corner)</param>
	/// <param name="angle">current angle for component</param>
	/// <param name="w">component width</param>
	/// <param name="h">component height</param>
	/// <param name="r">radious of the ship which contain component</param>
	Component(int stamina, sf::Color color, int x, int y, double angle, int w, int h, int r)
		:stamina(stamina), color(color), coord(x, y, angle, w, h), r(r)
	{
		active = false;
	}
	~Component() {};
	/// <summary>
	/// getter of private attribute stamina
	/// </summary>
	/// <returns>stamina</returns>
	int get_stamina();
	/// <summary>
	/// getter of private attribute active
	/// </summary>
	/// <returns>active</returns>
	bool get_active();
	/// <summary>
	/// method responsible for setting activeness of component
	/// </summary>
	/// <param name="active">true or false depends on if we want to enable it or disable</param>
	void set_active(bool active);
	/// <summary>
	/// getter of protedted attribute coordinates
	/// </summary>
	/// <returns>Currents coordinates of the component</returns>
	Coordinates get_coordinates();
	/// <summary>
	/// virtual method responsible for drawing component at the screen
	/// </summary>
	/// <returns></returns>
	virtual sf::RectangleShape draw();

};

/// <summary>
/// ChilClass of Component, Shield can belong only to BomberShip and it protect it from Ammunition objects
/// </summary>
class Shield : public Component
{
public:
	Shield();
	/// <summary>
	/// Constructor of the class Shield, initialize Component constructor and essenatial attributes
	/// 
	/// </summary>
	/// <param name="stamina">how many loop count component will be active</param>
	/// <param name="color">red or blue</param>
	/// <param name="x">x component coordinates(left upper corner)</param>
	/// <param name="y">y component coordinates(left upper corner)</param>
	/// <param name="angle">current angle for component</param>
	/// <param name="w">component width</param>
	/// <param name="h">component height</param>
	/// <param name="r">radious of the ship which contain component</param>
	Shield(int stamina, sf::Color color, int x, int y, double angle, int w, int h, int r)
		:Component(stamina, color, x, y, angle, w, h, r)
	{}
	~Shield() {};
	/// <summary>
	/// method responsible for updating Shield coordinates
	/// </summary>
	/// <param name="x">new x component coordinates (left upper corner)</param>
	/// <param name="y">new y component coordinates (left upper corner)</param>
	/// <param name="ang">current angle of the component</param>
	void update_coordinates(int x, int y, double ang);
	/// <summary>
	/// method responsible for drawing shield at the screen
	/// </summary>
	/// <returns>GGUI Rectange shaped object</returns>
	sf::RectangleShape draw();

};

/// <summary>
/// ChilClass of Component, Laser can belong only to CruiserShip and it protect it from Ammunition objects and enable special attack
/// </summary>
class Laser : public Component
{
private:
	int damage;
public:
	Laser();
	/// <summary>
	/// Constructor of the class Laser, initialize Component constructor and essenatial attributes
	/// 
	/// </summary>
	/// <param name="stamina">how many loop count component will be active</param>
	/// <param name="damage">how much damage laser will caouse during one loop count</param>
	/// <param name="color">red or blue</param>
	/// <param name="x">x component coordinates(left upper corner)</param>
	/// <param name="y">y component coordinates(left upper corner)</param>
	/// <param name="angle">current angle for component</param>
	/// <param name="w">component width</param>
	/// <param name="h">component height</param>
	/// <param name="r">radious of the ship which contain component</param>
	Laser(int stamina, int damage, sf::Color color, int x, int y, double angle, int w, int h, int r)
		:Component(stamina, color, x, y, angle, w, h, r), damage(damage)
	{}
	~Laser() {};
	/// <summary>
	/// method responsible for subtracting target life through laser
	/// </summary>
	/// <param name="target">Pointer at target ship</param>
	void attack(SpaceShip*);
	/// <summary>
	/// method responsible for destroing all living bullets created by ship agains which Laser is fighting
	/// </summary>
	/// <param name="gun">Pointer of the gun which belong to our enemy ship</param>
	void destroy_all_created_ammo(Gun*);
	/// <summary>
	/// method responsible for drawing laser at screen
	/// </summary>
	/// <returns>GGUI Rectange shaped object</returns>
	sf::RectangleShape draw();
	/// <summary>
	/// method responsible for updating Laser coordinates
	/// </summary>
	/// <param name="x">new x component coordinates (left upper corner)</param>
	/// <param name="y">new y component coordinates (left upper corner)</param>
	/// <param name="ang">current angle of the component</param>
	/// <param name="h">Length of the Laser object</param>
	void update_coordinates(int x, int y, double ang, int h);
};
#endif

