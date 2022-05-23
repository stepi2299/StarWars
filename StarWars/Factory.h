#ifndef __FACTORIES__
#define __FACTORIES__

#include "ships.h"
#include "guns.h"

using namespace std;


/// <summary>
/// class provide interface for factory which returns Gun and SpaceShip of one type: Design Pattern - Abstract Factory 
/// </summary>
class AbstractFactory
{
protected:
	string color;
	sf::Vector2i win_dims;
	int r, w, h, diff_between_ships, count, x, y, angle;
public:
	AbstractFactory(string color, int diff_between_ships, sf::Vector2i win_dims);
	~AbstractFactory() {}
	virtual Gun * create_gun() = 0;
	virtual SpaceShip * create_ship() = 0;
	void update_ships_count(int count);
};

/// <summary>
/// concrete factory class of Bombers
/// </summary>
class BomberFactory:public AbstractFactory
{
public:
	BomberFactory(string color, int diff_between_ships, sf::Vector2i win_dims) : AbstractFactory(color, diff_between_ships, win_dims)
	{
		r = 40;
		w = 20;
		h = 40;
	}
	Gun* create_gun() override;
	SpaceShip* create_ship() override;
};

/// <summary>
/// concrete factory class of Fighters
/// </summary>
class FighterFactory:public AbstractFactory
{
public:
	FighterFactory(string color, int diff_between_ships, sf::Vector2i win_dims) : AbstractFactory(color, diff_between_ships, win_dims)
	{
		r = 25;
		w = 8;
		h = 30;
	}
	Gun* create_gun() override;
	SpaceShip* create_ship() override;
};

/// <summary>
/// concrete factory class of Cruisers
/// </summary>
class CruiserFactory:public AbstractFactory
{
public:
	CruiserFactory(string color, int diff_between_ships, sf::Vector2i win_dims) : AbstractFactory(color, diff_between_ships, win_dims)
	{
		r = 35;
		w = 10;
		h = 30;
	}
	Gun* create_gun() override;
	SpaceShip* create_ship() override;
};
#endif
