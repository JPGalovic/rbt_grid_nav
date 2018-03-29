#pragma once
/**
 * Grid, Used to define a set of Cells for within a grid system.
 * @version 1.2.0
 * @author J.P.Galovic
 * @date March 2018
 */


#include "Cell.h"
#include "List.h"

#include <string>
#include <stdexcept>
#include <cstdlib>
#include <iostream>

template<class T>
class Grid
{
private:
	int fMinX, fMaxX, fMinY, fMaxY; // Grid Limits
	Cell<T> * fOrigin; // Origin of grid

public:
	Grid(Cell<T> & aOrigin); // Construct Grid from Cell
	Grid(T & aInitalValue, int aWidth, int aHeight); // Construct Grid from a Width, Height and Inital Value

	Cell<T> & getCell(int aX, int aY);
	Cell<T> & getCell(Coordinate & aCoordinate);

	T & getCellValue(int aX, int aY);
	
	int getMinX();
	int getMaxX();
	int getMinY();
	int getMaxY();

	int getWidth();
	int getHeight();

	void setCellValue(T & aValue, int aX, int aY);
};

template<class T>
inline Grid<T>::Grid(Cell<T>& aOrigin)
{
	// Traverse to Origin (0,0)
	Cell<T>* lCell = &aOrigin;
	while (lCell->getX() != 0)
	{
		if (lCell->getX() > 0)
			lCell = &lCell->getWest();
		else
			lCell = &lCell->getEast();
	}

	while (lCell->getY() != 0)
	{
		if (lCell->getY() > 0)
			lCell = &lCell->getNorth();
		else
			lCell = &lCell->getSouth();
	}

	fOrigin = lCell;

	// Get Min/Max
	// MinX
	while (lCell->hasEast())
		lCell = &lCell->getEast();
	fMaxX = lCell->getX();

	while (lCell->hasWest())
		lCell = &lCell->getWest();
	fMinX = lCell->getX();

	while (lCell->hasNorth())
		lCell = &lCell->getNorth();
	fMinY = lCell->getY();

	while (lCell->hasSouth())
		lCell = &lCell->getSouth();
	fMaxY = lCell->getY();
}

template<class T>
inline Grid<T>::Grid(T & aInitalValue, int aWidth, int aHeight)
{
	Cell<T>** lCellGrid;
	lCellGrid = new Cell<T>*[aWidth];
	for (int i = 0; i<aWidth; i++)
		lCellGrid[i] = new Cell<T>[aHeight];

	for (int j = 0; j < aHeight; j++)
	{
		for (int i = 0; i < aWidth; i++)
		{
			std::cout << "Setup Cell: (" << i << "," << j << ")" << std::endl;

			lCellGrid[i][j] = Cell<T>(aInitalValue, i, j);

			if (i > 0)
				lCellGrid[i][j].setWest(lCellGrid[i - 1][j]);

			if (j > 0)
				lCellGrid[i][j].setNorth(lCellGrid[i][j - 1]);
		}
	}

	// Traverse to Origin (0,0)
	Cell<T>* lCell = &lCellGrid[0][0];

	while (lCell->getX() != 0)
	{
		if (lCell->getX() > 0)
			lCell = &lCell->getWest();
		else
			lCell = &lCell->getEast();
	}

	while (lCell->getY() != 0)
	{
		if (lCell->getY() > 0)
			lCell = &lCell->getNorth();
		else
			lCell = &lCell->getSouth();
	}

	fOrigin = lCell;

	// Get Min/Max
	// MinX
	while (lCell->hasEast())
		lCell = &lCell->getEast();
	fMaxX = lCell->getX();

	while (lCell->hasWest())
		lCell = &lCell->getWest();
	fMinX = lCell->getX();

	while (lCell->hasNorth())
		lCell = &lCell->getNorth();
	fMinY = lCell->getY();

	while (lCell->hasSouth())
		lCell = &lCell->getSouth();
	fMaxY = lCell->getY();
}

template<class T>
inline Cell<T> & Grid<T>::getCell(int aX, int aY)
{
	if (aX > fMaxX)
		throw std::range_error("Error: X value greater than Max");
	if (aX < fMinX)
		throw std::range_error("Error: X value less than Min");
	if (aY > fMaxY)
		throw std::range_error("Error: Y value greater than Max");
	if (aY < fMinY)
		throw std::range_error("Error: Y value less than Min");

 	Cell<T>* lCell = fOrigin;
	while (lCell->getX() != aX)
	{
		if (lCell->getX() > aX)
			lCell = &lCell->getWest();
		else
			lCell = &lCell->getEast();
	}

	while (lCell->getY() != aY)
	{
		if (lCell->getY() > aY)
			lCell = &lCell->getNorth();
		else
			lCell = &lCell->getSouth();
	}

	return *lCell;
}

template<class T>
inline Cell<T>& Grid<T>::getCell(Coordinate & aCoordinate)
{
	return getCell(aCoordinate.getX(), aCoordinate.getY());
}

template<class T>
inline T & Grid<T>::getCellValue(int aX, int aY)
{
	return getCell(aX, aY).getValue();
}

template<class T>
inline int Grid<T>::getMinX()
{
	return fMinX;
}

template<class T>
inline int Grid<T>::getMaxX()
{
	return fMaxX;
}

template<class T>
inline int Grid<T>::getMinY()
{
	return fMinY;
}

template<class T>
inline int Grid<T>::getMaxY()
{
	return fMaxY;
}

template<class T>
inline int Grid<T>::getWidth()
{
	return std::abs(fMaxX - fMinX) + 1;
}

template<class T>
inline int Grid<T>::getHeight()
{
	return std::abs(fMaxY - fMinY) + 1;
}

template<class T>
inline void Grid<T>::setCellValue(T & aValue, int aX, int aY)
{
	getCell(aX, aY).setValue(aValue);
}
