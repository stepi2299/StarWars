#ifndef __FIGHT__
#define __FIGHT__

#include "SpaceShip.h"
#include <math.h>
class SpaceShip;
class Gun;

/// <summary>
/// Class responsible for handling duels between 2 ships from different teams
/// 
/// Object of this class is created in a main loop. It contains 2 pointers of SpaceShip class. Each Ship is from other team, blue or red
/// Fight is over when life one of the ships fall to 0. 
/// </summary>
class Fight
{
private:
	SpaceShip * redship, * blueship;
	string turn;
	/// <summary>
	/// method which randomly choose ship which starts from attack
	/// </summary>
	void who_is_starting();
	void switch_turn();
	int loop_count;
	int target_x, red_target_y, blue_target_y;
	double a, target_angle, angle_correction;
	/// <summary>
	/// method which returns angle between ships which is currently attacks' gun and middle of the defending ship
	/// </summary>
	/// <param name="defender">Pointer at ship which is currently defending</param>
	/// <param name="attacker">Pointer at gun of the ship which is currently attacking</param>
	/// <returns></returns>
	double calculate_angle(SpaceShip* defender, Gun* attacker);
	void fighting(SpaceShip* defender, SpaceShip* attacker);
public:
	/// <summary>
	/// attribute which tells if ships are on battle positions
	/// </summary>
	bool on_place;
	/// <summary>
	/// Constructor of the Fight class
	/// 
	/// this method initialize important attributes like for duel coordinates of the ships during fight, distance, who is starting etc.
	/// </summary>
	/// <param name="redship">Pointer at ship from redteam</param>
	/// <param name="blueship">Pointer at ship from blueteam</param>
	Fight(SpaceShip *redship, SpaceShip *blueship);
	/// <summary>
	/// basic method which run private method responsoble for fighting
	/// 
	/// this method checking who is now defending and attacking and setting parameters for the duel
	/// </summary>
	void choosing_fighters();
	/// <summary>
	/// method responsible for moving ships for position defined at constructor method
	/// 
	/// this method is called if attribute **on_place** is not set
	/// it setting moving direction for the ships
	/// </summary>
	void move_to_fighting_position();
	/// <summary>
	/// method returning if ships are on place for starting duel
	/// </summary>
	/// <returns>true if ships are at battle position, otherwise false</returns>
	bool get_on_place();
	/// <summary>
	/// method which set proper guns angle for fight
	/// 
	/// this method is called ony at the begining of the duel, when ships are on battle position
	/// it update ship which attacks gun's angle
	/// </summary>
	void battle_position();
	/// <summary>
	/// method which returns angle between ships which is currently attacks' gun and middle of the defending ship
	/// </summary>
	/// <param name="defender">Pointer at ship which is currently defending</param>
	/// <param name="attacker">Pointer at gun of the ship which is currently attacking</param>
	/// <returns>angle as a double</returns>
	double calculate_correct_angle(SpaceShip* defender, Gun* attacker);
	/// <summary>
	/// method responsible for updating position of all amunition produces by ships which are in the duel
	/// 
	/// method called at every iteration of the main loop
	/// </summary>
	void move_all_ammo();
	/// <summary>
	/// method responsible for returning specific ship pointer
	/// </summary>
	/// <param name="color">red or blue</param>
	/// <returns>SpaceShip pointer edpends on color</returns>
	SpaceShip* get_ship(string);
	/// <summary>
	/// method responsible for cleaning after fight. It remove al unnecessary items like ammo, guns, special_amm etc. when fight is over
	/// </summary>
	void destroy_waste_after_fight();
	~Fight() 
	{
		destroy_waste_after_fight();
	}
};
#endif