#pragma once
/**
 * Cell Container, Used to define a cell used part of a grid system
 * @version 1.2.0
 * @author J.P.Galovic
 * @date March 2018
 */


#include "Cell.h"

#include <stdexcept>

template<class T>
class Grid
{
private:
	int fMinX, fMaxX, fMinY, fMaxY; // Grid Limits
	Cell<T> * fOrigin; // Origin of grid

	Grid()
	{
		fWidth = 0; fHeight = 0;
		fOrigin = nullptr;
	}

public:
	Grid(const Cell<T> & aOrigin);

	void setCellValue(int aX, int aY, const T & aValue);

	const Cell<T> & getCell(int aX, int aY) const;
	const T & getCellValue(int aX, int aY) const;

	const int getMinX() const;
	const int getMaxX() const;
	const int getMinY() const;
	const int getMaxY() const;

	const int getWitdh() const;
	const int getHeight() const;
};

template<class T>
Grid<T>::Grid(Cell<T> & aCell)
{
	// Find Cell 0,0. Assume complete grid (no gaps) and assume that 0,0 exists
	// Find Horizontal
	Cell<T> * lCell = & aCell;
	while (lCell->getX() != 0)
	{
		if (lCell->getX() > 0)
			lCell = &lCell->getWest();
		else
			lCell = &lCell->getEast();
	}

	while (lCell->getY() != 0)
	{
		if (lCell->getY() < 0)
			lCell = &lCell->getSouth();
		else
			lCell = &lCell->getNorth();
	}

	fOrigin = lCell;

	// Get MinX
	while (lCell->hasWest())
		lCell = &lCell->getWest();
	fMinX = lCell->getX();

	// Get MaxX
	while (lCell->hasEast())
		lCell = &lCell->getEast();
	fMaxX = lCell->getX();

	// Get MinY
	while (lCell->hasSouth())
		lCell = &lCell->getSouth();
	fMaxY = lCell->getY();

	// Get MaxY
	while (lCell->hasNorth())
		lCell = &lCell->getNorth();
	fMinY = lCell->getY();
}

template<class T>
void Grid<T>::setCellValue(int aX, int aY, const T & aValue)
{
	// Get Cell
	Cell<T> * lCell = fOrigin;

	// Set Got
	lCell->setValue(aValue);
}

template<class T>
const Cell<T>& Grid<T>::getCell(int aX, int aY) const
{
	// Check Cell is in range
	if (aX < fMinX || aX > fMaxX)
		throw std::out_of_range("X coordinate out of range.");
	if (aY < fMinY || aY > fMaxY)
		throw std::out_of_range("Y coordinate out of range.");

	// Navigate to Cell
	const Cell<T> * lCell = (Cell<T>*)fOrigin;
	while (lCell->getX() != aX)
	{
		if (lCell->getX() > aX)
			lCell = &lCell->getWest();
		else
			lCell = &lCell->getEast();
	}

	while (lCell->getY() != aY)
	{
		if (lCell->getY() < aY)
			lCell = &lCell->getSouth();
		else
			lCell = &lCell->getNorth();
	}

	return *lCell;
}

template<class T>
const T & Grid<T>::getCellValue(int aX, int aY) const
{
	return getCell(aX, aY).getValue();
}

template<class T>
const int Grid<T>::getMinX() const
{
	return fMinX;
}

template<class T>
const int Grid<T>::getMaxX() const
{
	return fMaxX;
}

template<class T>
const int Grid<T>::getMinY() const
{
	return fMinY;
}

template<class T>
const int Grid<T>::getMaxY() const
{
	return fMaxY;
}

template<class T>
const int Grid<T>::getWitdh() const
{
	return (fMaxX - fMinX) + 1;
}

template<class T>
const int Grid<T>::getHeight() const
{
	return (fMaxY - fMinY) + 1;
}
