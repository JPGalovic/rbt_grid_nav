#pragma once

/**
 * Cell Container
 */

template <class T>
class Cell
{
private:
	int fX, fY; // Coordiates of Cell
	Cell<T> * fNorth; Cell<T> * fEast; Cell<T> * fSouth; Cell<T> * fWest; // Connections to Adjasent Cells
	T fValue;

	

public:
	Cell()
	{
		fX = 0; fY = 0;
		fNorth = nullptr; fEast = nullptr; fSouth = nullptr; fWest = nullptr;
		fValue = T();
	}

	Cell(const T & aValue, int aX, int aY);

	void setNorth(Cell<T> & aCell);
	void setEast(Cell<T> & aCell);
	void setSouth(Cell<T> & aCell);
	void setWest(Cell<T> & aCell);
	void remove();

	const T & getValue() const;
	const Cell<T> & getNorth() const;
	const Cell<T> & getEast() const;
	const Cell<T> & getSouth() const;
	const Cell<T> & getWest() const;

	const bool hasNorth() const;
	const bool hasEast() const;
	const bool hasSouth() const;
	const bool hasWest() const;

	const int getX() const;
	const int getY() const;
};

/**
 * Initalises values of Cell
 */
template<class T>
Cell<T>::Cell(const T & aValue, int aX, int aY)
{
	fX = aX; fY = aY;
	fNorth = nullptr; fEast = nullptr; fSouth = nullptr; fWest = nullptr;
	fValue = aValue;
}

/**
 * Sets pointer to the Cell to the North.
 */
template<class T>
void Cell<T>::setNorth(Cell<T> & aCell)
{
	aCell.fSouth = this;

	if (fNorth != nullptr)
	{
		aCell.fNorth = fNorth;
		fNorth->fSouth = &aCell;
	}

	fNorth = &aCell;
}

/**
 * Sets pointer to the Cell to the East.
 */
template<class T>
void Cell<T>::setEast(Cell<T> & aCell)
{
	aCell.fWest = this;

	if (fEast != nullptr)
	{
		aCell.fEast = fEast;
		fEast->fWest = &aCell;
	}

	fEast = &aCell;
}

/**
 * Sets pointer to the Cell to the South.
 */
template<class T>
void Cell<T>::setSouth(Cell<T> & aCell)
{
	aCell.fNorth = this;

	if (fSouth != nullptr)
	{
		aCell.fSouth = fSouth;
		fSouth->fNorth = &aCell;
	}

	fSouth = &aCell;
}

/**
 * Sets pointer to the Cell to the West.
 */
template<class T>
void Cell<T>::setWest(Cell<T> & aCell)
{
	aCell.fEast = this;

	if (fWest != nullptr)
	{
		aCell.fWest = fWest;
		fWest->fEast = &aCell;
	}

	fWest = &aCell;
}

/**
 * Removes this node from the Grid
 */
template<class T>
void Cell<T>::remove()
{
	if (fNorth != nullptr)
		fNorth->fSouth = nullptr;
	if (fEast != nullptr)
		fEast->fWest = nullptr;
	if (fSouth != nullptr)
		fSouth->fNorth = nullptr;
	if (fWest != nullptr)
		fWest->fEast = nullptr;
}

/**
 * Returns the cell value.
 */
template<class T>
const T & Cell<T>::getValue() const
{
	return fValue;
}

/**
 * Returns the cell to the North.
 */
template<class T>
const Cell<T> & Cell<T>::getNorth() const
{
	return *fNorth;
}

/**
 * Returns the cell to the East.
 */
template<class T>
const Cell<T> & Cell<T>::getEast() const
{
	return *fEast;
}

/**
 * Returns the cell to the South.
 */
template<class T>
const Cell<T> & Cell<T>::getSouth() const
{
	return *fSouth;
}

/**
 * Returns the cell to the West.
 */
template<class T>
const Cell<T> & Cell<T>::getWest() const
{
	return *fWest;
}

template<class T>
const bool Cell<T>::hasNorth() const
{
	return fNorth != nullptr;
}

template<class T>
const bool Cell<T>::hasEast() const
{
	return fEast != nullptr;
}

template<class T>
const bool Cell<T>::hasSouth() const
{
	return fSouth != nullptr;
}

template<class T>
const bool Cell<T>::hasWest() const
{
	return fWest != nullptr;
}

/**
 * Gets the X coordinate.
 */
template<class T>
const int Cell<T>::getX() const
{
	return fX;
}

/**
 * Gets the Y coordinate.
 */
template<class T>
const int Cell<T>::getY() const
{
	return fY;
}
