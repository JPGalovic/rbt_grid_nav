#pragma once
/**
 * Agent, Keeps track of position in Grid and contains algorithems for both informed and uninformed navigation options.
 * @version 1.0.0
 * @author J.P.Galovic
 * @date March 2018
 */

#include"Grid.h"

class Agent
{
private:
	Coordinate fStart;
	Coordinate fLocation;
	Coordinate fGoal;

public:
	Agent();
	Agent(int aX, int aY);

	void setGoal(int aX, int aY);

	int getX();
	int getY();
	int getGoalX();
	int getGoalY();

	// Movement Processes
	bool moveNorth(Cell<std::string>& aNorth);
	bool moveSouth(Cell<std::string>& aSouth);
	bool moveEast(Cell<std::string>& aEast);
	bool moveWest(Cell<std::string>& aWest);

	// Goal Checking
	bool atGoal();
	bool isAt(int aX, int aY);
	bool goalAt(int aX, int aY);

	// AI Algorithems
	//int DFS(Grid<std::string> aGrid);
	//int BFS(Grid<std::string> aGrid);

	//int GBFS(Grid<std::string> aGrid);
	bool AS(Grid<std::string> & aGrid);
	bool ASMove(Grid<std::string> & aGrid, Grid<int> aFScore, int aLifeTime);
	int heuristicCostEstimate(Grid<std::string> aGrid, Coordinate aFrom, Coordinate aTo);

	//int US(Grid<std::string> aGrid);
	//int IS(Grid<std::string> aGrid);
};