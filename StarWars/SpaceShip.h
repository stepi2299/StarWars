#ifndef __Ships__
#define __Ships__

#include <vector>
#include "Coordinates.h"
#include "Gun.h"
#include <cstring>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Fight.h"

using namespace std;

class Gun;

class SpaceShip
{
private:
	int life, max_guns;
	float dodge_chances, special_attack_chances;
	string type, color;
	bool check_dodge();
	bool check_special_attack();
	ShipCoordinates coordinates;
	vector <Gun*> armory;
	sf::Color sf_color;
	bool fighting;
protected:
	int stamina;
	friend class Fight;

public:
	SpaceShip();
	SpaceShip(int life, int max_guns, float dodge_chances, float special_attack_chances, string type, string color, int x, int y, int angle, int r, Gun &gun);
	~SpaceShip() {}
	void take_gun(Gun &g);
	void drop_the_gun();
	bool can_take_gun(Gun &g);
	void attack(SpaceShip* ship);
	void dodge();
	virtual void special_attack(SpaceShip* ship) = 0;
	ShipCoordinates get_coordinates();
	void move(int x, int y);
	SpaceShip find_oponent();  // rethink about if none is found
	int get_current_life();
	void subtract_life(int damage);
	void destroy();
	sf::CircleShape draw();

};
#endif
