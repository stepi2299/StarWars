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
	WarSide(int shipscount, string color);
	~WarSide() {};
	VShips vships;
	void attack();
	void defend();
	bool end_round();
	void prepare_for_next_round();
	void initialize();
};
#endif
