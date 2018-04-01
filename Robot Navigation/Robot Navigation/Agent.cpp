#include "Agent.h"
#include "Coordinate.h"
#include "List.h"
#include "GridPrinters.h"

#include <limits>
#include <chrono>
#include <thread>

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

void Agent::setStart(int aX, int aY)
{
	fStart.setX(aX);
	fStart.setY(aY);
	gotoStart();
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

void Agent::gotoStart()
{
	fLocation.setX(fStart.getX());
	fLocation.setY(fStart.getY());
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
			//printGrid(lGScore);
			//system("PAUSE");
			//printGrid(lFScore);
			//system("PAUSE");
			//printGrid(lCameFrom);
			//system("PAUSE");
			List<Coordinate> * lPath = rebuildPath(lCameFrom, lCurrent);
			return ASMove(aGrid, lPath, 1000);
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
					if (!(aGrid.getCell(lCurrent->getNorth().getCoordinate()).getValue() == "WAL"))
						lDirection = &lCurrent->getNorth();
				break;
			case 1:
				if (lCurrent->hasSouth())
					if (!(aGrid.getCell(lCurrent->getSouth().getCoordinate()).getValue() == "WAL"))
						lDirection = &lCurrent->getSouth();
				break;
			case 2:
				if (lCurrent->hasEast())
					if (!(aGrid.getCell(lCurrent->getEast().getCoordinate()).getValue() == "WAL"))
						lDirection = &lCurrent->getEast();
				break;
			case 3:
				if (lCurrent->hasWest())
					if (!(aGrid.getCell(lCurrent->getWest().getCoordinate()).getValue() == "WAL"))
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
bool Agent::ASMove(Grid<std::string>& aGrid, List<Coordinate> * aPath, int aLifeTime)
{
	enum Cardinal { NORTH, EAST, SOUTH, WEST};
	
	for (int j = 0; j < aLifeTime; j++)
	{
		Cardinal lDirectionToCheck;
		Cardinal lDirectionToMove;
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
				else
					continue;
				break;
			case 1:
				if (aGrid.getCell(fLocation).hasEast())
					lDirectionToCheck = EAST;
				else
					continue;
				break;
			case 2:
				if (aGrid.getCell(fLocation).hasSouth())
					lDirectionToCheck = SOUTH;
				else
					continue;
				break;
			case 3:
				if (aGrid.getCell(fLocation).hasWest())
					lDirectionToCheck = WEST;
				else
					continue;
				break;
			default:
				continue;
			}

			int lCost = std::numeric_limits<int>::max();

			switch (lDirectionToCheck)
			{
			case NORTH:
				if (aPath->get(0) == aGrid.getCell(fLocation).getNorth().getCoordinate())
				{
					lDirectionToMove = lDirectionToCheck;
					aPath->remove(aPath->get(0));
				}
				break;
			case EAST:
				if (aPath->get(0) == aGrid.getCell(fLocation).getEast().getCoordinate())
				{
					lDirectionToMove = lDirectionToCheck;
					aPath->remove(aPath->get(0));
				}
				break;
			case SOUTH:
				if (aPath->get(0) == aGrid.getCell(fLocation).getSouth().getCoordinate())
				{
					lDirectionToMove = lDirectionToCheck;
					aPath->remove(aPath->get(0));
				}
				break;
			case WEST:
				if (aPath->get(0) == aGrid.getCell(fLocation).getWest().getCoordinate())
				{
					lDirectionToMove = lDirectionToCheck;
					aPath->remove(aPath->get(0));
				}
				break;
			default:
				break;
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
		std::this_thread::sleep_for(std::chrono::seconds(1));
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

List<Coordinate> * Agent::rebuildPath(Grid<Coordinate>& aGrid, Cell<std::string>* aCurrent)
{
	List<Coordinate> lPath;
	lPath.push_front(aCurrent->getCoordinate());

	Coordinate lCurrent = aCurrent->getCoordinate();

	while (lCurrent != fStart)
	{
		std::cout << "Pathing from: " << lCurrent.getX() << "," << lCurrent.getY();
		lCurrent = aGrid.getCell(lCurrent).getValue();
		std::cout << " to: " << lCurrent.getX() << "," << lCurrent.getY() << std::endl;
		lPath.push_front(lCurrent);
	}

	return &lPath;
}
