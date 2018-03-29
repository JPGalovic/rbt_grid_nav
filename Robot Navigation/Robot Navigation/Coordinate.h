#pragma once
/**
 * Coordinate, used to define a x-y coordinate.
 * @version 1.2.0
 * @author J.P.Galovic
 * @date March 2018
 */

class Coordinate
{
private:
	int fX, fY;

public:
	Coordinate();
	Coordinate(int aX, int aY);

	int getX();
	int getY();

	void setCoordinate(int aX, int aY);
	void setCoordinate(Coordinate & aCoordinate);
	void setX(int aX);
	void setY(int aY);

	bool operator==(Coordinate & aOther);
};