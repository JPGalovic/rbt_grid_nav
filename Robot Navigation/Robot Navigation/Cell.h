#pragma once

/**
 * Cell Container
 */

template <class T>
class Cell
{
private:
	int fX, fY; // Coordiates of Cell
	Cell * fNorth, fEast, fSouth, fWest; // Connections to Adjasent Cells
	T fValue;

	Cell()
	{
		fX = 0; fY = 0;
		fNorth = nullptr; fEast = nullptr; fSouth = nullptr; fWest = nullptr;
		fValue = T();
	}

public:
	Cell(const T & aValue, int aX, int aY);

	void setNorth(Cell & aCell);
	void setEast(Cell & aCell);
	void setSouth(Cell & aCell);
	void setWest(Cell & aCell);
	void remove();

	const T & getValue() const;
	const Cell & getNorth() const;
	const Cell & getEast() const;
	const Cell & getSouth() const;
	const Cell & getWest() const;

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
void Cell<T>::setNorth(Cell & aCell)
{
	aCell.fSouth = this;
	fNorth = &aCell;
}

/**
 * Sets pointer to the Cell to the East.
 */
template<class T>
void Cell<T>::setEast(Cell & aCell)
{
	aCell.fWest = this;
	fEast = &aCell;
}

/**
 * Sets pointer to the Cell to the South.
 */
template<class T>
void Cell<T>::setSouth(Cell & aCell)
{
	aCell.fNorth = this;
	fSouth = &aCell;
}

/**
 * Sets pointer to the Cell to the West.
 */
template<class T>
void Cell<T>::setWest(Cell & aCell)
{
	aCell.fEast = this;
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
