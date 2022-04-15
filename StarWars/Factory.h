#ifndef __FACTORIES__
#define __FACTORIES__

#include "ships.h"

using namespace std;

class AbstractFactory
{
	virtual Gun create_gun() = 0;
	virtual SpaceShip create_ship() = 0;
};

class BomberFactory:public AbstractFactory
{
	Gun create_gun() override;
	SpaceShip create_ship() override;
};

class FighterFactory:public AbstractFactory
{
	Gun create_gun() override;
	SpaceShip create_ship() override;
};

class CruiserFactory:public AbstractFactory
{
	Gun create_gun() override;
	SpaceShip create_ship() override;
};
#endif
