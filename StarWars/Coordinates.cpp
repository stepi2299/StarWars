#include "Coordinates.h"
Coordinates::Coordinates(int x, int y, int angle, int w, int h):
	x(x), y(y), w(w), h(h), angle(angle)
{
}

Coordinates::Coordinates()
{
}

ShipCoordinates::ShipCoordinates()
{
}
ShipCoordinates::ShipCoordinates(int x, int y, int angle, int r) :
	x(x), y(y), r(r), angle(angle)
{
}
