#include "Agent.h"
#include "GridPrinters.h"

#include <iostream>
#include <string>
#include <Windows.h>

void setWall(Grid<std::string> & aCellGrid, int aX, int aY, int aW, int aH)
{
	for (int j = 0; j < aH; j++)
		for (int i = 0; i < aW; i++)
			aCellGrid.setCellValue(std::string("WAL"), aX + i, aY + j);
}

int main(int argc, char** argv)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 8);

	// Setup Grid Structure, TODO: Setup Better Way to do this;
	const int lGridWitdh = 11; // TODO: Read from file.
	const int lGridHeight = 5; // TODO: Read from file.

	Cell<std::string> lCellGrid[lGridWitdh][lGridHeight] = { Cell<std::string>() };

	for (int j = 0; j < lGridHeight; j++)
	{
		for (int i = 0; i < lGridWitdh; i++)
		{
			std::cout << "Setup Cell: (" << i << "," << j << ")" << std::endl;

			lCellGrid[i][j] = Cell<std::string>(std::string("CLR"), i, j);

			if (i > 0)
				lCellGrid[i][j].setWest(lCellGrid[i - 1][j]);

			if (j > 0)
				lCellGrid[i][j].setNorth(lCellGrid[i][j - 1]);
		}
	}
	

	SetConsoleTextAttribute(hConsole, 15);
	std::cout << std::endl << "Grid Setup" << std::endl;

	

	Grid<std::string> lGrid(lCellGrid[0][0]);

	// Set Walls
	setWall(lGrid, 2, 0, 2, 2);
	setWall(lGrid, 8, 0, 1, 2);
	setWall(lGrid, 10, 0, 1, 1);
	setWall(lGrid, 2, 3, 1, 2);
	setWall(lGrid, 3, 4, 3, 1);
	setWall(lGrid, 9, 3, 1, 1);
	setWall(lGrid, 8, 4, 2, 1);

	Agent lAgent(0, 1);
	lAgent.setGoal(10, 3);
	system("PAUSE");

	printGrid(lGrid, lAgent);
	system("PAUSE");

	lAgent.AS(lGrid);

	system("PAUSE");
	return 0;
}