#include "SpaceShip.h"

SpaceShip::SpaceShip()
{
	cout << "SpaceShip" << endl;
}

SpaceShip::SpaceShip(int life, int max_guns, int dodge_chances, int special_attack_chances, string type, string color, int x, int y, int angle, int r, Gun *gun):
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
	speed = 1;
	dodge_speed = 3;
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
	if ((current_armory_state < max_guns) && type==gun->get_type())
		return true;
	else
		return false;
}

void SpaceShip::drop_the_gun()
{
	armory.pop_back();  // TODO so far last gun but in the future we can select which erase
}


bool SpaceShip::is_dodge()
{
	int dodge_rand = rand() % 20;
	if (dodge_chances >= dodge_rand)
		return true;
	else
		return false;
}

void SpaceShip::dodge(int target_x)
{
	if (is_avoiding == 0)
	{
		if (target_x == coordinates.x)
			increase = true;
		else
			increase = false;
	}
	if (increase == 1)
	{
		if (coordinates.x == target_x + coordinates.r*2)
			is_avoiding = false;
		else
		{
			move(target_x + coordinates.r*2, coordinates.y);
			is_avoiding = true;
		}
	}
	else if (increase == 0)
		if (coordinates.x == target_x)
			is_avoiding = false;
		else
		{
			move(target_x, coordinates.y);
			is_avoiding = true;
		}
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
		//destroy();
	}
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

void SpaceShip::move(int target_x, int target_y)
{
	ang = 0;
	int move_speed = speed;
	if ((is_avoiding == 1) && (coordinates.x - target_x < coordinates.r) && (increase == 1))
		move_speed = dodge_speed;
	else if ((is_avoiding == 1) && (coordinates.x - target_x > coordinates.r) && (increase == 0))
		move_speed = dodge_speed;
	if (coordinates.x == target_x)
	{
		moveX = 0;
		if (coordinates.y < target_y)
			moveY = speed;
		else if (coordinates.y > target_y)
			moveY = -speed;
		else
			moveY = 0;
	}
	else
	{
		moveY = 0;
		if (coordinates.x < target_x)
			moveX = speed;
		else if (coordinates.x > target_x)
			moveX = -speed;
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
		if (coordinates.angle > 270)
		{
			ang = -speed;
			moveX = 0;
		}
		else if (coordinates.angle < 270)
		{
			ang = speed;
			moveX = 0;
		}
	}
	else if (moveX < 0)
	{
		if (coordinates.angle > 90)
		{
			ang = -speed;
			moveX = 0;
		}
		else if (coordinates.angle < 90)
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
	is_avoiding = false;
	fighting = false;
}
