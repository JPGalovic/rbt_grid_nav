#pragma once
/**
 * Cell Container, Used to define a cell used part of a grid system
 * @version 1.2.0
 * @author J.P.Galovic
 * @date March 2018
 */

template<class T>
class Cell
{
private:
	int fX, fY; // Coordinates of Cell, used to determine Origin (0,0) as well as dertermining if accessed cell is correct cell
	Cell<T> * fNorth; Cell<T> * fSouth; Cell<T> * fEast; Cell<T> * fWest; // Pointers to adjacent Cells
	T fValue; // Value of Cell

public:
	Cell();
	Cell(T & aValue, int aX, int aY);

	void setValue(T & aValue);
	
	// Connection Setters
	void setNorth(Cell<T> & aCell);
	void setSouth(Cell<T> & aCell);
	void setEast(Cell<T> & aCell);
	void setWest(Cell<T> & aCell);

	void remove();

	T & getValue();
	
	// Get Connections
	Cell<T> & getNorth();
	Cell<T> & getSouth();
	Cell<T> & getEast();
	Cell<T> & getWest();

	int getX();
	int getY();

	bool hasNorth();
	bool hasSouth();
	bool hasEast();
	bool hasWest();
};

template<class T>
inline Cell<T>::Cell()
{
	fX = 0; fY = 0;
	fNorth = nullptr; fSouth = nullptr; fEast = nullptr; fWest = nullptr;
	fValue = T();
}

template<class T>
inline Cell<T>::Cell(T & aValue, int aX, int aY)
{
	fX = aX; fY = aY;
	fNorth = nullptr; fSouth = nullptr; fEast = nullptr; fWest = nullptr;
	fValue = aValue;
}

template<class T>
inline void Cell<T>::setValue(T & aValue)
{
	fValue = aValue;
}

template<class T>
inline void Cell<T>::setNorth(Cell<T>& aCell)
{
	aCell.fSouth = this;
	fNorth = &aCell;
}

template<class T>
inline void Cell<T>::setSouth(Cell<T>& aCell)
{
	aCell.fNorth = this;
	fSouth = &aCell;
}

template<class T>
inline void Cell<T>::setEast(Cell<T>& aCell)
{
	aCell.fWest = this;
	fEast = &aCell;
}

template<class T>
inline void Cell<T>::setWest(Cell<T>& aCell)
{
	aCell.fEast = this;
	fWest = &aCell;
}

template<class T>
inline void Cell<T>::remove()
{
}

template<class T>
inline T & Cell<T>::getValue()
{
	return fValue;
}

template<class T>
inline Cell<T> & Cell<T>::getNorth()
{
	return *fNorth;
}

template<class T>
inline Cell<T> & Cell<T>::getSouth()
{
	return *fSouth;
}

template<class T>
inline Cell<T> & Cell<T>::getEast()
{
	return *fEast;
}

template<class T>
inline Cell<T> & Cell<T>::getWest()
{
	return *fWest;
}

template<class T>
inline int Cell<T>::getX()
{
	return fX;
}

template<class T>
inline int Cell<T>::getY()
{
	return fY;
}

template<class T>
inline bool Cell<T>::hasNorth()
{
	return fNorth != nullptr;
}

template<class T>
inline bool Cell<T>::hasSouth()
{
	return fSouth != nullptr;
}

template<class T>
inline bool Cell<T>::hasEast()
{
	return fEast != nullptr;
}

template<class T>
inline bool Cell<T>::hasWest()
{
	return fWest != nullptr;
}
