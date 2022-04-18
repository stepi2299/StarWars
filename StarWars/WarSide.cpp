#include "WarSide.h"
#include "Factory.h"

WarSide::WarSide(int shipscount, string color) : shipscount(shipscount), color(color)
{
	int diff_between_ships = 100;
	BomberFactory b_factory = BomberFactory(color, diff_between_ships);
	CruiserFactory c_factory = CruiserFactory(color, diff_between_ships);
	FighterFactory f_factory = FighterFactory(color, diff_between_ships);

	for (int i = 0; i < shipscount; i++)
	{
		int rand_num = (rand() % 3);
		if (rand_num == 0)
		{
			b_factory.update_ships_count(i);
			BomberShip ship = b_factory.create_ship();
			vships.push_back(&ship);
		}
		else if (rand_num == 1)
		{
			c_factory.update_ships_count(i);
			CruiserShip ship = c_factory.create_ship();
			vships.push_back(&ship);
		}
		else
		{
			f_factory.update_ships_count(i);
			FighterShip ship = f_factory.create_ship();
			vships.push_back(&ship);
		}
	}
}
