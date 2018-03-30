#include "Coordinate.h"

Coordinate::Coordinate()
{
	fX = 0;
	fY = 0;
}

Coordinate::Coordinate(int aX, int aY)
{
	fX = aX;
	fY = aY;
}

int Coordinate::getX()
{
	return fX;
}

int Coordinate::getY()
{
	return fY;
}

void Coordinate::setCoordinate(int aX, int aY)
{
	fX = aX;
	fY = aY;
}

void Coordinate::setCoordinate(Coordinate & aCoordinate)
{
	fX = aCoordinate.getX();
	fY = aCoordinate.getY();
}

void Coordinate::setX(int aX)
{
	fX = aX;
}

void Coordinate::setY(int aY)
{
	fY = aY;
}

bool Coordinate::operator==(Coordinate & aOther)
{
	return fX == aOther.fX && fY == aOther.fY;
}

bool Coordinate::operator!=(Coordinate & aOther)
{
	return !(*this == aOther);
}
