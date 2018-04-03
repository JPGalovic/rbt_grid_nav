#pragma once

#include "Grid.h"
#include "List.h"
#include "Cardinal.h"

#include <string>
#include <limits>
#include <stdexcept>

/**
 * Implementation of the A Star 
 */
template<class T>
class AStar
{
private:
	Coordinate fStart;
	Coordinate fGoal;

	Grid<T> * fGrid;

	T fBlock; // defines blocked node

	List<Cardinal> constructPath(Grid<Cardinal> & aCameFromGrid);
	int heuristicCostEstimate(Coordinate & aFrom, Coordinate & aTo);
	int calculateDistance(Coordinate & aFrom, Coordinate & aTo);
public:
	AStar(Coordinate & aStart, Coordinate & aGoal, Grid<T> & aGrid, T & aBlock);

	List<Cardinal> search();
};

/**
 * Constructs Path based on the Came From Grid (generated as part of the algorithem)
 * @param aCameFromGrid
 */
template<class T>
inline List<Cardinal> AStar<T>::constructPath(Grid<Cardinal> & aCameFromGrid)
{
	List<Cardinal> lList;
	Coordinate lCell = fGoal;

	while (lCell != fStart) // While came from grid is not pointing to the start coordinate
	{
		Cardinal lDirection = aCameFromGrid.getCell(lCell).getValue();
		

		switch (lDirection)
		{
		case NORTH:
			lDirection = SOUTH;
			lCell = aCameFromGrid.getCell(lCell).getNorth().getCoordinate();
			break;
		case WEST:
			lDirection = EAST;
			lCell = aCameFromGrid.getCell(lCell).getWest().getCoordinate();
			break;
		case SOUTH:
			lDirection = NORTH;
			lCell = aCameFromGrid.getCell(lCell).getSouth().getCoordinate();
			break;
		case EAST:
			lDirection = WEST;
			lCell = aCameFromGrid.getCell(lCell).getEast().getCoordinate();
			break;
		default:
			break;
		}

		lList.push_front(lDirection);
	}

	return lList;
}

/**
 * Calculates huristic cost for traveling from node to node.
 * Calculation value is depenand on the flags set in the algorithem
 * Any combination of the differnt options avalible are run as the sum of all type's selected
 * @param aFrom, node to calulate from.
 * @param aTo, node to calculate to.
 * @return sum of heuristics cast to int
 * @return euclidian distance, manhatten distance, eucledian + manhattan distance
 */
template<class T>
inline int AStar<T>::heuristicCostEstimate(Coordinate & aFrom, Coordinate & aTo)
{
	// If either aFrom or aTo is block then return infinity
	if (fGrid->getCell(aFrom).getValue() == fBlock || fGrid->getCell(aTo).getValue() == fBlock)
		return std::numeric_limits<int>::max();

	// Calculate Distance Heuristic
	int lXDist = std::abs(aFrom.getX() - aTo.getX());
	int lYDist = std::abs(aFrom.getY() - aTo.getY());
	int lManhattan = lXDist + lYDist;
	int lEuclidian = std::sqrt((lXDist * lXDist) + (lYDist * lYDist));
	return lManhattan + lEuclidian;
}

/**
 * Calculates the distance between nodes.
 * @param aFrom, node from.
 * @param aTo, node to.
 * @return Euclidian Distance
 */
template<class T>
inline int AStar<T>::calculateDistance(Coordinate & aFrom, Coordinate & aTo)
{
	// Calculate Euclidian Distance
	int lXDist = std::abs(aFrom.getX() - aTo.getX());
	int lYDist = std::abs(aFrom.getY() - aTo.getY());
	int lEuclidian = std::sqrt((lXDist * lXDist) + (lYDist * lYDist));
	return lEuclidian;
}

/**
 * Constructs algorithem, setting required values to run algorithem
 * @param aStart, Starting Coordinate of Agent.
 * @param aGoal, Goal Coordinate of Agent.
 * @param aGrid, Grid to Search.
 * @param aBlock, Value of a Blocked Node, Any node with this value cannot be accessed by Agent.
 */
template<class T>
inline AStar<T>::AStar(Coordinate & aStart, Coordinate & aGoal, Grid<T> & aGrid, T & aBlock)
{
	fStart = aStart;
	fGoal = aGoal;
	fGrid = & aGrid;
	fBlock = aBlock;
}

/**
 * Runs search. Code Generated based on psudo code avalible at https://en.wikipedia.org/wiki/A*_search_algorithm
 * @return List of Coordinates for Agent to follow (path).
 * @throw If a path cannot be found from Start to Goal, then method throws with error. "No path to goal found."
 */
template<class T>
inline List<Cardinal> AStar<T>::search()
{
	// Lists of open and closed nodes.
	// Open list gets starting location added to it.
	List<Coordinate> lOpen; List<Coordinate> lClosed;
	lOpen.add(fStart);

	// Map contining best path.
	Cardinal lNone = NONE;
	Grid<Cardinal> lCameFrom(lNone, fGrid->getWidth(), fGrid->getHeight());

	// Map containing cost to get to node from start. inital is infinity
	// Cost of moving from start to start is 0.
	int lInfinity = std::numeric_limits<int>::max();
	Grid<int> lGScore(lInfinity, fGrid->getWidth(), fGrid->getHeight());
	int lTempGScore = 0;
	lGScore.getCell(fStart).setValue(lTempGScore);

	// Map containing cost to get from start to goal via node.
	// Cost of moving from start to goal is purily heuristic
	Grid<int> lFScore(lInfinity, fGrid->getWidth(), fGrid->getHeight());
	int lTempFScore = heuristicCostEstimate(fStart, fGoal);
	lFScore.getCell(fStart).setValue(lTempFScore);

	// While open list is not empty...
	while (!lOpen.empty())
	{
		// Get next from open list with lowest FScore.
		Cell<T> * lCurrent = &fGrid->getCell(lOpen[0]);
		int lCurrentValue = lFScore.getCell(lOpen[0]).getValue();

		for (int i = 0; i < lOpen.size(); i++)
			if (lFScore.getCell(lOpen[i]).getValue() < lCurrentValue)
			{
				lCurrent = & fGrid->getCell(lOpen[i]);
				lCurrentValue = lFScore.getCell(lOpen[i]).getValue();
			}

		std::cout << "Checking Cell (" << lCurrent->getX() << ", " << lCurrent->getY() << "): ";

		// Check if current cell is goal.
		if (lCurrent->getCoordinate() == fGoal)
		{
			std::cout << "Goal!" << std::endl;
			return constructPath(lCameFrom);
		}

		// Move current from open to closed list.
		lOpen.remove(lCurrent->getCoordinate());
		lClosed.add(lCurrent->getCoordinate());

		// Check each direction and add to open list if not in open or closed lists.
		for (int i = 0; i < 4; i++)
		{
			Cardinal lCameFromDirection = NONE;
			Cell<T> * lDirection = nullptr;
			switch (i)
			{
			case 0:
				if (lCurrent->hasNorth())
					if (lCurrent->getNorth().getValue() != fBlock)
					{
						lCameFromDirection = SOUTH;
						lDirection = &lCurrent->getNorth();
						break;
					}
				continue;
			case 1:
				if (lCurrent->hasSouth())
					if (lCurrent->getSouth().getValue() != fBlock)
					{
						lCameFromDirection = NORTH;
						lDirection = &lCurrent->getSouth();
						break;
					}
				continue;
			case 2:
				if (lCurrent->hasEast())
					if (lCurrent->getEast().getValue() != fBlock)
					{
						lCameFromDirection = WEST;
						lDirection = &lCurrent->getEast();
						break;
					}
				continue;
			case 3:
				if (lCurrent->hasWest())
					if (lCurrent->getWest().getValue() != fBlock)
					{
						lCameFromDirection = EAST;
						lDirection = &lCurrent->getWest();
						break;
					}
				continue;
			}

			// If direction has alredy being checked (is in closed set) continue.
			if (lClosed.hasValue(lDirection->getCoordinate()))
				continue;
			// If not in open set then add as a newly found node
			if (!lOpen.hasValue(lDirection->getCoordinate()))
				lOpen.add(lDirection->getCoordinate());

			// Calculate GScore & FScore of Direction
			lTempGScore = lGScore.getCell(lCurrent->getCoordinate()).getValue() + calculateDistance(lCurrent->getCoordinate(), lDirection->getCoordinate());
			
			// If not a better path to node, continue to next node
			if (lTempGScore >= lGScore.getCell(lDirection->getCoordinate()).getValue())
				continue;

			// This is the best path yet, so record it.
			lCameFrom.getCell(lDirection->getCoordinate()).setValue(lCameFromDirection);
			lGScore.getCell(lDirection->getCoordinate()).setValue(lTempGScore);
			lTempFScore = lTempGScore + heuristicCostEstimate(lDirection->getCoordinate(), fGoal);
			lFScore.getCell(lDirection->getCoordinate()).setValue(lTempFScore);
		}
	}

	// Reached end of open list without finding path to goal. throw error???
	throw std::runtime_error("No path to goal found.");
}
