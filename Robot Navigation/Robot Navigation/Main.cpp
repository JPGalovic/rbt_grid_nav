#include "Agent.h"
#include "GridPrinters.h"

#include <iostream>
#include <sstream>
#include <fstream>
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
	std::ifstream lInputFile;
	std::string lLine;

	lInputFile.open(argv[1], std::ios::in);
	if (!lInputFile)
	{
		std::cerr << "Unable to open file " << argv[1] << std::endl;
		system("PAUSE");
		return 1;
	}

	int n = 0;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 8);

	Grid<std::string> lGrid;
	Agent lAgent;

	while (std::getline(lInputFile, lLine))
	{
		std::cout << n << ": " << lLine << std::endl;
		std::stringstream lLineStream(lLine);
		int lX; int lY; int lW; int lH; // Temp Buffers
		

		if (n == 0) // Set Grid Size
		{
			lLineStream.get();
			lLineStream >> lH;
			lLineStream.get();
			lLineStream >> lW;

			lGrid = Grid<std::string>(std::string("CLR"), lW, lH);

			std::cout << "Grid Size Read As: [" << lH << ',' << lW << "]" << std::endl;
		}
		else if (n == 1) // Set Agent Start Position
		{
			lLineStream.get();
			lLineStream >> lX;
			lLineStream.get();
			lLineStream >> lY;

			lAgent.setStart(lX, lY);

			std::cout << "Agent Start Position Read As: (" << lX << ',' << lY << ")" << std::endl;
		}
		else if (n == 2) // Set Agent Goal
		{
			lLineStream.get();
			lLineStream >> lX;
			lLineStream.get();
			lLineStream >> lY;

			lAgent.setGoal(lX, lY);

			std::cout << "Agent Goal Position Read As: (" << lX << ',' << lY << ")" << std::endl;
		}
		else // Set Grid Walls
		{
			lLineStream.get();
			lLineStream >> lX;
			lLineStream.get();
			lLineStream >> lY;
			lLineStream.get();
			lLineStream >> lW;
			lLineStream.get();
			lLineStream >> lH;

			setWall(lGrid, lX, lY, lW, lH);
			std::cout << "Wall Location Read As: (" << lX << ',' << lY << "," << lW << ',' << lH << ")" << std::endl;
		}

		n++;
	}
	
	system("PAUSE");

	printGrid(lGrid, lAgent);
	system("PAUSE");

	lAgent.AS(lGrid);

	system("PAUSE");
	return 0;
}