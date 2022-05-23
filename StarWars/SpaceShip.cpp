#include "SpaceShip.h"

SpaceShip::SpaceShip()
{
	cout << "SpaceShip" << endl;
}

SpaceShip::SpaceShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string color, int x, int y, int angle, int r, Gun *gun):
	coordinates(x, y, angle, r), life(life), max_guns(max_guns), defend_chances(dodge_chances), special_attack_chances(special_attack_chances), color(color)
{
	take_gun(gun);
	active_round = 0;
	fighting = false;
	if (color == "red")
		sf_color = sf::Color::Red;
	else if (color == "blue")
		sf_color = sf::Color::Blue;
	else
		cout << "Wrong color" << endl;
	speed = 1;
	is_avoiding = false;
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
	if (current_armory_state < max_guns)
		return true;
	else
		return false;
}

void SpaceShip::drop_the_gun()
{
	armory.pop_back();  // TODO so far last gun but in the future we can select which erase
}


bool SpaceShip::is_defending()
{
	int dodge_rand = rand() % 50;
	if (defend_chances >= dodge_rand)
		return true;
	else
		return false;
}

bool SpaceShip::is_special_attack()
{
	int attack_rand = rand() % 2000;
	if (special_attack_chances >= attack_rand)
		return true;
	else
		return false;
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
	{
		life = 0;
	}
	else
		life = life - damage;
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

void SpaceShip::move(int target_x, int target_y, int current_speed)
{
	ang = 0;
	int move_speed = current_speed;
	if (move_speed == 0)
		move_speed = this->speed;
	if (coordinates.x == target_x)
	{
		moveX = 0;
		if (coordinates.y < target_y)
			moveY = move_speed;
		else if (coordinates.y > target_y)
			moveY = -move_speed;
		else
			moveY = 0;
	}
	else
	{
		moveY = 0;
		if (coordinates.x < target_x)
			moveX = move_speed;
		else if (coordinates.x > target_x)
			moveX = -move_speed;
		else
			moveX = 0;
	}

	for (auto i = armory.begin(); i < armory.end(); i++)
		(*i)->move(moveX, moveY, ang);
}

void SpaceShip::rotate()
{
	if (moveY > 0)
	{
		if (coordinates.angle > 0)
		{
			ang = -speed;
			moveY = 0;
		}
		else if (coordinates.angle < 0)
		{
			ang = speed;
			moveY = 0;
		}
	}
	else if (moveY < 0)
	{
		if (coordinates.angle > 180)
		{
			ang = -speed;
			moveY = 0;
		}
		else if (coordinates.angle < 180)
		{
			ang = speed;
			moveY = 0;
		}
	}
	else if (moveX > 0)
	{
		if (coordinates.angle > -90 && coordinates.get_def_angl() == 0)
		{
			ang = -speed;
			moveX = 0;
		}
		else if (coordinates.angle < 270 && coordinates.get_def_angl() == 180)
		{
			ang = speed;
			moveX = 0;
		}
	}
	else if (moveX < 0)
	{
		if (coordinates.angle > 90 && coordinates.get_def_angl() == 180)
		{
			ang = -speed;
			moveX = 0;
		}
		else if (coordinates.angle < 90 && coordinates.get_def_angl() == 0)
		{
			ang = speed;
			moveX = 0;
		}
	}
	for (auto i = armory.begin(); i < armory.end(); i++)
		(*i)->move(moveX, moveY, ang);
}

void SpaceShip::update_position()
{
	coordinates.x += moveX;
	coordinates.y += moveY;
	coordinates.angle += ang;

	for (auto i = armory.begin(); i < armory.end(); i++)
		(*i)->update_coord_gun();

	moveX = 0;
	moveY = 0;
	ang = 0;
}

void SpaceShip::reset_after_fight()
{
	after_round();
	fighting = false;
	for (auto gun = armory.begin(); gun < armory.end(); gun++)
	{
		for (auto ammo = (*gun)->magazine.begin(); ammo < (*gun)->magazine.begin(); ammo++)
			delete (*ammo);
		(*gun)->magazine.clear();
	}
	for (auto bomb = special_magazine.begin(); bomb < special_magazine.end(); bomb++)
		delete* bomb;
	special_magazine.clear();
	if(life>0)
		base();
}



double SpaceShip::calculate_ships_angle(SpaceShip* ship)
{
	ShipCoordinates attacker_coord = ship->get_coordinates();
	if (coordinates.x - attacker_coord.x == 0)
		return 0;
	double a = (coordinates.y - attacker_coord.y) / (coordinates.x - attacker_coord.x);
	double ang =  90.0 - Gun::rad_into_degrees(atan(abs(a)));
	if (((coordinates.x < attacker_coord.x) && (coordinates.y > attacker_coord.y)) || ((coordinates.x > attacker_coord.x) && (coordinates.y < attacker_coord.y)))
		return ang;
	else
		return -ang;
}

void SpaceShip::base()
{
	coordinates.angle = coordinates.get_def_angl();
}
