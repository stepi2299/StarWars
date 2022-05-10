#include "WarSide.h"
#include "Factory.h"

WarSide::WarSide(int shipscount, string color, sf::Vector2i win_dims) : shipscount(shipscount), color(color)
{
	int diff_between_ships = win_dims.x/(shipscount+1);
	BomberFactory b_factory = BomberFactory(color, diff_between_ships, win_dims);
	CruiserFactory c_factory = CruiserFactory(color, diff_between_ships, win_dims);
	FighterFactory f_factory = FighterFactory(color, diff_between_ships, win_dims);

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

vector <Fight*> WarSide::find_opponents(WarSide& other_side)
{
	bool tmp_fighting, opponent_fighting;
	float distance;
	vector <Fight*> vfights;
	for (auto i = vships.begin(); i < vships.end(); i++)
	{
		float min_distance = INFINITY;
		tmp_fighting = (*i)->get_fighting();
		SpaceShip* opponent= (*i); // only because it didn't want to compile, but always it should be overwrite by opponents ships if fight will be create
		bool found = false;
		if (tmp_fighting == 1)
			continue;
		else
		{
			for (auto j = other_side.vships.begin(); j < other_side.vships.end(); j++)
			{
				opponent_fighting = (*j)->get_fighting();
				if (opponent_fighting == 1)
					continue;
				else
				{
					distance = (*i)->get_distance_between_ships(*j);
					if (distance < min_distance)
					{
						found = true;
						min_distance = distance;
						opponent = *j;
					}
				}
			}
			if (found == 1)
			{
				(*i)->set_fighting(true); //redteam
				opponent->set_fighting(true);  // blueteam
				Fight* fight = new Fight((*i), opponent);
				vfights.push_back(fight);  // check if it is working
			}
		}
	}
	return vfights;
}
