#include "Agent.h"
#include "Coordinate.h"
#include "List.h"
#include "GridPrinters.h"

#include <limits>

Agent::Agent()
{
	fStart = Coordinate(0, 0);
	fLocation = Coordinate(0, 0);
	fGoal = Coordinate(0, 0);
}

Agent::Agent(int aX, int aY)
{
	fStart = Coordinate(aX, aY);
	fLocation = Coordinate(aX, aY);
	fGoal = Coordinate(0, 0);
}

void Agent::setGoal(int aX, int aY)
{
	fGoal.setX(aX);
	fGoal.setY(aY);
}

int Agent::getX()
{
	return fLocation.getX();
}

int Agent::getY()
{
	return fLocation.getY();
}

int Agent::getGoalX()
{
	return fGoal.getX();
}

int Agent::getGoalY()
{
	return fGoal.getY();
}

bool Agent::moveNorth(Cell<std::string>& aNorth)
{
	if (aNorth.getValue() == "CLR")
	{
		fLocation.setCoordinate(aNorth.getCoordinate());
		return true;
	}
	return false;
}

bool Agent::moveSouth(Cell<std::string>& aSouth)
{
	if (aSouth.getValue() == "CLR")
	{
		fLocation.setCoordinate(aSouth.getCoordinate());
		return true;
	}
	return false;
}

bool Agent::moveEast(Cell<std::string>& aEast)
{
	if (aEast.getValue() == "CLR")
	{
		fLocation.setCoordinate(aEast.getCoordinate());
		return true;
	}
	return false;
}

bool Agent::moveWest(Cell<std::string>& aWest)
{
	if (aWest.getValue() == "CLR")
	{
		fLocation.setCoordinate(aWest.getCoordinate());
		return true;
	}
	return false;
}

bool Agent::atGoal()
{
	return fLocation.getX() == fGoal.getX() && fLocation.getY() == fGoal.getY();
}

bool Agent::isAt(int aX, int aY)
{
	return aX == fLocation.getX() && aY == fLocation.getY();
}

bool Agent::goalAt(int aX, int aY)
{
	return aX == fGoal.getX() && aY == fGoal.getY();
}

/**
 * A* (A Star) search algorithem. Developed with information and pseduo code from https://en.wikipedia.org/wiki/A*_search_algorithm
 * @date MAR18
 * @author J.P.Galovic
 */
bool Agent::AS(Grid<std::string> & aGrid)
{
	// Get width and height of grid
	int lHeight = aGrid.getHeight();
	int lWidth = aGrid.getWidth();

	// Set of nodes alredy evaluated
	List<Coordinate> lClosedSet;

	// Set of descovered nodes, Initalise with starting location node
	List<Coordinate> lOpenSet;
	lOpenSet.add(fStart); //Only start node is initally known

	// Map (grid) to containing most efficent path to node.
	Grid<Coordinate> lCameFrom(Coordinate(), aGrid.getWidth(), aGrid.getHeight());

	// Map (grid) to contain cost of getting from start node to that node
	int lInifinity = std::numeric_limits<int>::max();
	Grid<int> lGScore(lInifinity, aGrid.getWidth(), aGrid.getHeight());

	// Cost of going from start to start is 0
	int lValue = 0;
	lGScore.getCell(fStart).setValue(lValue);

	// Map (grid) to contain cost of getting from Start node to End node via This node.
	Grid<int> lFScore(lInifinity, aGrid.getWidth(), aGrid.getHeight());

	// Cost of going from start to end is completly heuristic
	int lCost = heuristicCostEstimate(aGrid, fStart, fGoal);
	lFScore.getCell(fStart).setValue(lCost);

	while (!lOpenSet.empty())
	{
		// Get next from Open Set with lowest FScore Value
		Cell<std::string>* lCurrent = &aGrid.getCell(lOpenSet[0]);
		int lCurrentValue = lFScore.getCell(lOpenSet[0]).getValue();

		std::cout << "Checking Cell (" << lCurrent->getCoordinate().getX() << ", " << lCurrent->getCoordinate().getY() << ")" << std::endl;

		for (int i = 0; i < lOpenSet.size(); i++)
		{
			Coordinate lCoord = lOpenSet[0];
			int lTestValue = lFScore.getCell(lCoord).getValue();
			if (lTestValue < lCurrentValue)
			{
				lCurrent = &aGrid.getCell(lOpenSet[i]);
				lCurrentValue = lFScore.getCell(lOpenSet[i]).getValue();
			}
		}

		if (lCurrent->getCoordinate() == fGoal)
		{
			printGrid(lFScore);
			system("PAUSE");
			return ASMove(aGrid, lFScore, 1000);
		}
			

		// Move current to Closed Set
		lOpenSet.remove(lCurrent->getCoordinate());
		lClosedSet.add(lCurrent->getCoordinate());

		for (int i = 0; i < 4; i++)
		{
			Cell<std::string>* lDirection = lCurrent;
			switch (i)
			{
			case 0:
				if (lCurrent->hasNorth())
					lDirection = &lCurrent->getNorth();
				break;
			case 1:
				if (lCurrent->hasSouth())
					lDirection = &lCurrent->getSouth();
				break;
			case 2:
				if (lCurrent->hasEast())
					lDirection = &lCurrent->getEast();
				break;
			case 3:
				if (lCurrent->hasWest())
					lDirection = &lCurrent->getWest();	
				break;
			default:
				break;
			}
			if (!lClosedSet.hasValue(lDirection->getCoordinate())) // alredy addressed continue to next direction
			{
				if (!lOpenSet.hasValue(lDirection->getCoordinate())) // descovery of new node, add it to the open set to be checked.
					lOpenSet.add(lDirection->getCoordinate());

				// get distance from start to direction;
				int lTemp_GScore = lGScore.getCell(lCurrent->getCoordinate()).getValue() + 1;
				if (lTemp_GScore < lGScore.getCell(lDirection->getCoordinate()).getValue()) // check if path is better
				{
					// path is better, record it.
					lCameFrom.getCell(lDirection->getCoordinate()).setValue(lCurrent->getCoordinate());
					lGScore.getCell(lDirection->getCoordinate()).setValue(lTemp_GScore);
					int lTemp_FScore = heuristicCostEstimate(aGrid, lDirection->getCoordinate(), fGoal);
					if (lTemp_FScore != std::numeric_limits<int>::max())
						lTemp_FScore += lTemp_GScore;
					lFScore.getCell(lDirection->getCoordinate()).setValue(lTemp_FScore);
				}
			}
		}
	}
	// Failure to path find path
	return false;
}

/**
 * AS Move, runs movements of AS Alogrithem, North Movement Bias.
 */
bool Agent::ASMove(Grid<std::string>& aGrid, Grid<int> aFScore, int aLifeTime)
{
	enum Cardinal { NORTH, EAST, SOUTH, WEST};
	
	for (int j = 0; j < aLifeTime; j++)
	{
		Cardinal lDirectionToCheck;
		Cardinal lDirectionToMove = NORTH;
		int lCostToMove = std::numeric_limits<int>::max();

		// Check if at goal
		if (atGoal())
		{
			std::cout << "At Goal" << std::endl;
			return true;
		}

		// Determine what direction to move
		for (int i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 0:
				if (aGrid.getCell(fLocation).hasNorth())
					lDirectionToCheck = NORTH;
				break;
			case 1:
				if (aGrid.getCell(fLocation).hasEast())
					lDirectionToCheck = EAST;
				break;
			case 2:
				if (aGrid.getCell(fLocation).hasSouth())
					lDirectionToCheck = SOUTH;
				break;
			case 3:
				if (aGrid.getCell(fLocation).hasWest())
					lDirectionToCheck = WEST;
				break;
			default:
				continue;
			}

			int lCost = std::numeric_limits<int>::max();

			switch (lDirectionToCheck)
			{
			case NORTH:
				lCost = aFScore.getCell(fLocation).getNorth().getValue();
				break;
			case EAST:
				lCost = aFScore.getCell(fLocation).getEast().getValue();
				break;
			case SOUTH:
				lCost = aFScore.getCell(fLocation).getSouth().getValue();
				break;
			case WEST:
				lCost = aFScore.getCell(fLocation).getWest().getValue();
				break;
			}

			if (lCost < lCostToMove)
			{
				lDirectionToMove = lDirectionToCheck;
				lCostToMove = lCost;
			}
		}

		// Move
		switch (lDirectionToMove)
		{
		case NORTH:
			moveNorth(aGrid.getCell(fLocation).getNorth());
			break;
		case EAST:
			moveEast(aGrid.getCell(fLocation).getEast());
			break;
		case SOUTH:
			moveSouth(aGrid.getCell(fLocation).getSouth());
			break;
		case WEST:
			moveWest(aGrid.getCell(fLocation).getWest());
			break;
		default:
			break;
		}

		// print Grid Graphic
		printGrid(aGrid, *this);
		system("PAUSE");
	}
	return false;
}

int Agent::heuristicCostEstimate(Grid<std::string> aGrid, Coordinate aFrom, Coordinate aTo)
{
	if (aGrid.getCell(aFrom).getValue() == "WAL")
		return std::numeric_limits<int>::max();

	// Calculate Distance Heuristic
	int lXDist = std::abs(aFrom.getX() - aTo.getX());
	int lYDist = std::abs(aFrom.getY() - aTo.getY());
	int lManhattan = lXDist + lYDist;
	int lEuclidian = std::sqrt((lXDist * lXDist) + (lYDist * lYDist));
	return lManhattan + lEuclidian;
}