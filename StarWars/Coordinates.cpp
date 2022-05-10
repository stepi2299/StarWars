#include "Coordinates.h"
Coordinates::Coordinates(int x, int y, double angle, int w, int h):
	x(x), y(y), w(w), h(h), angle(angle), default_angle(angle)
{
}

Coordinates::Coordinates()
{
}
double Coordinates::get_def_angl()
{
	return default_angle;
}

double Coordinates::get_battle_angle()
{
	return battle_angle;
}

void Coordinates::set_battle_angle(double b_angle)
{
	battle_angle = default_angle + b_angle;
}

ShipCoordinates::ShipCoordinates()
{
}
ShipCoordinates::ShipCoordinates(int x, int y, int angle, int r) :
	x(x), y(y), r(r), angle(angle), default_angle(angle)
{
}

int ShipCoordinates::get_def_angl()
{
	return default_angle;
}

AmmoCoordinates::AmmoCoordinates()
{
}
AmmoCoordinates::AmmoCoordinates(double x, double y, double angle, int w, int h) :
	x(x), y(y), w(w), h(h), angle(angle)
{
}

double AmmoCoordinates::get_def_angl()
{
	return angle;
}


