#include "SpaceShip.h"

SpaceShip::SpaceShip()
{
	cout << "SpaceShip" << endl;
}

SpaceShip::SpaceShip(int life, int max_guns, float dodge_chances, float special_attack_chances, string type, string color, int x, int y, int angle, int r, Gun *gun):
	coordinates(x, y, angle, r), life(life), max_guns(max_guns), dodge_chances(dodge_chances), special_attack_chances(special_attack_chances), type(type), color(color)
{
	take_gun(gun);
	fighting = false;
	if (color == "red")
		sf_color = sf::Color::Red;
	else if (color == "blue")
		sf_color = sf::Color::Blue;
	else
		cout << "Wrong color" << endl;
}

void SpaceShip::take_gun(Gun *g)
{
	bool permission = can_take_gun(g);
	if (permission == 1)
	{
		armory.push_back(g);
	}
	else
		cout << "Can not take this gun" << endl;
}

bool SpaceShip::can_take_gun(Gun *gun)
{
	int current_armory_state = armory.size();
	if ((current_armory_state < max_guns) && type==gun->get_type())
		return true;
	else
		return false;
}

void SpaceShip::drop_the_gun()
{
	armory.pop_back();  // TODO so far last gun but in the future we can select which erase
}

void SpaceShip::attack(SpaceShip* ship)
{
	//TODO
}

void SpaceShip::dodge()
{

}

ShipCoordinates SpaceShip::get_coordinates()
{
	return coordinates;
}

int SpaceShip::get_current_life()
{
	return life;
}

void SpaceShip::subtract_life(int damage)
{
	if (life <= damage)
		destroy();
	else
		life = life - damage;
}

void SpaceShip::destroy()
{
	// TODO 
}

sf::CircleShape SpaceShip::draw()
{
	sf::CircleShape circle = sf::CircleShape(coordinates.r);
	circle.setOrigin(sf::Vector2f(coordinates.r, coordinates.r));
	circle.setFillColor(sf_color);
	circle.setPosition(coordinates.x, coordinates.y);
	return circle;
}

bool SpaceShip::get_fighting()
{
	return fighting;
}

void SpaceShip::set_fighting(bool fight)
{
	if (fight != fighting)
		fighting = fight;
	else
		cout << "Ship is already in current state: fighting = " << fighting << endl;
}

float SpaceShip::get_distance_between_ships(SpaceShip* ship)
{
	ShipCoordinates target_coord = ship->get_coordinates();
	return sqrt(pow(target_coord.x - coordinates.x, 2) + pow(target_coord.y - coordinates.y, 2));
}