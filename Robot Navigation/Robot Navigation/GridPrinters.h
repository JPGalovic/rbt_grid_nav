#pragma once

#include "Grid.h"
#include "Agent.h"

#include <string>

void printGrid(Grid<std::string> & aGrid, Agent & aAgent);
void printGrid(Grid<std::string> & aGrid);
void printGrid(Grid<Coordinate> & aGrid);
void printGrid(Grid<int> & aGrid);
