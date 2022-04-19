#ifndef __WARSIDE__
#define __WARSIDE__

#include <vector>
#include "SpaceShip.h"

class WarSide
{
private:
	typedef vector <SpaceShip*> VShips;
	string color;
	int shipscount;
public:
	WarSide(int shipscount, string color, sf::Vector2i win_dims);
	~WarSide() {};
	VShips vships;
	void attack();
	void defend();
	bool end_round();
	vector <Fight*> find_opponents(WarSide& other_side);
	void prepare_for_next_round();
};
#endif
