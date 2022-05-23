#ifndef __WARSIDE__
#define __WARSIDE__

#include <vector>
#include "SpaceShip.h"

/// <summary>
/// Class responsible for ships and fights creation 
/// </summary>
class WarSide
{
private:
	typedef vector <SpaceShip*> VShips;
	string color;
	int shipscount;
public:
	/// <summary>
	/// Constructor responsible for creating given number of the ships, randomly choosing type
	/// </summary>
	/// <param name="shipscount">number of the ships in the team in game</param>
	/// <param name="color">red or blue</param>
	/// <param name="win_dims">dimension of the screen</param>
	WarSide(int shipscount, string color, sf::Vector2i win_dims);
	~WarSide() {};
	VShips vships;
	/// <summary>
	/// method responsible for finding opponents for ships in team
	/// </summary>
	/// <param name="other_side">other side object</param>
	/// <returns>vector of created fights></returns>
	vector <Fight*> find_opponents(WarSide& other_side);
};
#endif
