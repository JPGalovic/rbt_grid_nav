#include "Agent.h"
#include "Coordinate.h"
#include "List.h"
#include "GridPrinters.h"
#include "AStar.h"
#include "ListPrinters.h"

#include <limits>
#include <chrono>
#include <thread>
#include <stdexcept>

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

bool Agent::move(Cardinal aDirection, Cell<std::string> & aCurrent)
{
	switch (aDirection)
	{
	case NORTH:
		if(aCurrent.hasNorth())
			return moveNorth(aCurrent.getNorth());
		break;
	case WEST:
		if (aCurrent.hasWest())
			return moveNorth(aCurrent.getWest());
		break;
	case SOUTH:
		if (aCurrent.hasSouth())
			return moveNorth(aCurrent.getSouth());
		break;
	case EAST:
		if (aCurrent.hasEast())
			return moveNorth(aCurrent.getEast());
		break;
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
 * AS Move, runs movements of AS Alogrithem, North Movement Bias.
 */
bool Agent::ASMove(Grid<std::string>& aGrid)
{
	AStar<std::string> lAlgorithem(fStart, fGoal, aGrid, std::string("WAL"));
	try
	{
		List<Cardinal> lPath = lAlgorithem.search();

		PrintList(lPath);
		system("PAUSE");

		for (int n = 0; n < lPath.size(); n++)
		{
			move(lPath[n], aGrid.getCell(fLocation));
			printGrid(aGrid, *this);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		if(atGoal())
		{
			std::cout << "Arrived at Goal in " << lPath.size() << " Steps." << std::endl;
			return true;
		}
		else
		{
			std::cout << "Have not arrived at Goal in " << lPath.size() << " Steps." << std::endl;
			return false;
		}
	}
	catch (const std::runtime_error & e)
	{
		std::cout << e.what() << std::endl;
	}
	return false;
}