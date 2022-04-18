#include "WarSide.h"
#include "Factory.h"

WarSide::WarSide(int shipscount, string color) : shipscount(shipscount), color(color)
{
	BomberFactory b_factory = BomberFactory(color, 100);
	CruiserFactory c_factory = CruiserFactory(color, 100);
	FighterFactory f_factory = FighterFactory(color, 100);

	for (int i = 0; i < shipscount; i++)
	{
		int rand_num = (rand() % 3);
		SpaceShip* ship;
		if (rand_num == 0)
		{
			b_factory.update_ships_count(i);
			ship = b_factory.create_ship();
		}
		else if (rand_num == 1)
		{
			c_factory.update_ships_count(i);
			ship = c_factory.create_ship();
		}
		else
		{
			f_factory.update_ships_count(i);
			ship = f_factory.create_ship();
		}
		vships.push_back(ship);
	}
}
