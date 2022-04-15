#ifndef __GAMETURN__
#define __GAMETURN__
#include "WarSide.h"

class GameTurn
{
private:
	int turning_count;
	WarSide red_team;
	WarSide blue_team;
public:
	void initialize();
	void start_turn();
	void prepare_for_the_next_round();
	bool is_game_over();

};
#endif


