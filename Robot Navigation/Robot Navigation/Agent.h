#pragma once
/**
 * Agent, Keeps track of position in Grid and contains algorithems for both informed and uninformed navigation options.
 * @version 1.0.0
 * @author J.P.Galovic
 * @date March 2018
 */

#include"Grid.h"
#include"Cardinal.h"

class Agent
{
private:
	Coordinate fStart;
	Coordinate fLocation;
	Coordinate fGoal;

public:
	Agent();
	Agent(int aX, int aY);

	void setStart(int aX, int aY);
	void setGoal(int aX, int aY);

	int getX();
	int getY();
	int getGoalX();
	int getGoalY();

	void gotoStart();

	// Movement Processes
	bool moveNorth(Cell<std::string>& aNorth);
	bool moveSouth(Cell<std::string>& aSouth);
	bool moveEast(Cell<std::string>& aEast);
	bool moveWest(Cell<std::string>& aWest);
	bool move(Cardinal aDirection, Cell<std::string> & aCurrent);

	// Goal Checking
	bool atGoal();
	bool isAt(int aX, int aY);
	bool goalAt(int aX, int aY);

	// AI Algorithems
	bool ASMove(Grid<std::string> & aGrid);
};