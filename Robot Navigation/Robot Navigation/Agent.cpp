#include "Agent.h"

#include <vector>

Agent::Agent()
{
	fX = 0;
	fY = 0;
	fGoalX = 0;
	fGoalY = 0;
}

Agent::Agent(int aX, int aY)
{
	fX = aX;
	fY = aY;
	fGoalX = 0;
	fGoalY = 0;
}

void Agent::setGoal(int aX, int aY)
{
	fGoalX = aX;
	fGoalY = aY;
}

int Agent::getX()
{
	return fX;
}

int Agent::getY()
{
	return fY;
}

int Agent::getGoalX()
{
	return fGoalX;
}

int Agent::getGoalY()
{
	return fGoalY;
}

bool Agent::moveNorth(Cell<std::string>& aNorth)
{
	if (aNorth.getValue() == "CLR")
	{
		fX = aNorth.getX();
		fY = aNorth.getY();
		return true;
	}
	return false;
}

bool Agent::moveSouth(Cell<std::string>& aSouth)
{
	if (aSouth.getValue() == "CLR")
	{
		fX = aSouth.getX();
		fY = aSouth.getY();
		return true;
	}
	return false;
}

bool Agent::moveEast(Cell<std::string>& aEast)
{
	if (aEast.getValue() == "CLR")
	{
		fX = aEast.getX();
		fY = aEast.getY();
		return true;
	}
	return false;
}

bool Agent::moveWest(Cell<std::string>& aWest)
{
	if (aWest.getValue() == "CLR")
	{
		fX = aWest.getX();
		fY = aWest.getY();
		return true;
	}
	return false;
}

bool Agent::atGoal()
{
	return fX == fGoalX && fY == fGoalY;
}

bool Agent::isAt(int aX, int aY)
{
	return aX == fX && aY == fY;
}

bool Agent::goalAt(int aX, int aY)
{
	return aX == fGoalX && aY == fGoalY;
}

int Agent::AS(Grid<std::string> & aGrid)
{
	// Get width and height of grid
	int lHeight = aGrid.getHeight();
	int lWidth = aGrid.getWidth();

	// Set of nodes alredy evaluated
	std::vector<Cell<std::string>*> lClosedSet;

	// Set of descovered nodes, Initalise with starting location node
	std::vector<Cell<std::string>*> lOpenSet;
	lOpenSet[0] = &aGrid.getCell(0, 0);



	return 0;
}
