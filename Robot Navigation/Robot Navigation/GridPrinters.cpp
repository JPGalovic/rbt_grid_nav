#include "GridPrinters.h"

#include <windows.h>

void printGrid(Grid<std::string> & aGrid, Agent & aAgent)
{
	// Print Grid
	system("CLS");
	std::cout << "Grid Size: [" << aGrid.getWidth() << "," << aGrid.getHeight() << "]" << std::endl;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int j = 0; j < aGrid.getHeight(); j++)
	{
		for (int i = 0; i < aGrid.getWidth(); i++)
		{
			if (aAgent.isAt(i, j))
			{
				SetConsoleTextAttribute(hConsole, 11);
				std::cout << " " << "AGT";
				continue;
			}
			if (aAgent.goalAt(i, j))
			{
				SetConsoleTextAttribute(hConsole, 14);
				std::cout << " " << "GOL";
				continue;
			}
			if (aGrid.getCell(i, j).getValue() == "CLR")
				SetConsoleTextAttribute(hConsole, 10);
			if (aGrid.getCell(i, j).getValue() == "WAL")
				SetConsoleTextAttribute(hConsole, 12);
			std::cout << " " << aGrid.getCell(i, j).getValue();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
}

void printGrid(Grid<int> & aGrid)
{
	// Print Grid
	system("CLS");
	std::cout << "Grid Size: [" << aGrid.getWidth() << "," << aGrid.getHeight() << "]" << std::endl;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int j = 0; j < aGrid.getHeight(); j++)
	{
		for (int i = 0; i < aGrid.getWidth(); i++)
		{
			std::cout << " " << aGrid.getCell(i, j).getValue();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
}

void printGrid(Grid<Coordinate> & aGrid)
{
	// Print Grid
	system("CLS");
	std::cout << "Grid Size: [" << aGrid.getWidth() << "," << aGrid.getHeight() << "]" << std::endl;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int j = 0; j < aGrid.getHeight(); j++)
	{
		for (int i = 0; i < aGrid.getWidth(); i++)
		{
			std::cout << " (" << aGrid.getCell(i, j).getValue().getX() << "," << aGrid.getCell(i, j).getValue().getY() << ")";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
}

void printGrid(Grid<std::string> & aGrid)
{
	// Print Grid
	system("CLS");
	std::cout << "Grid Size: [" << aGrid.getWidth() << "," << aGrid.getHeight() << "]" << std::endl;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int j = 0; j < aGrid.getHeight(); j++)
	{
		for (int i = 0; i < aGrid.getWidth(); i++)
		{
			std::cout << " " << aGrid.getCell(i, j).getValue();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
}

