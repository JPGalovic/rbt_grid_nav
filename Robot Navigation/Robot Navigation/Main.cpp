#include "Grid.h"

#include <iostream>
#include <string>

void setWall(Grid <std::string>* aCellGrid, int aX, int aY, int aH, int aW)
{
	std::string lWall = "wal";
	for (int j = 0; j < aH; j++)
		for (int i = 0; i < aW; i++)
			aCellGrid->setCellValue(aX + i, aY + j, lWall);
}

int main()
{
	Cell<std::string> lOrigin("clr", 0, 0);

	Cell<std::string> * lCell = &lOrigin;

	// Setup Grid Structure, TODO: Setup Better Way to do this;
	const int lGridWitdh = 11; // TODO: Read from file.
	const int lGridHeight = 5; // TODO: Read from file.

	Cell<std::string> lCellGrid[lGridWitdh][lGridHeight] = { Cell<std::string>() };

	for (int j = 0; j < lGridHeight; j++)
	{
		for (int i = 0; i < lGridWitdh; i++)
		{
			std::cout << "Setup Cell: (" << i << "," << j << ")" << std::endl;

			lCellGrid[i][j] = Cell<std::string>("clear", i, j);

			if (i > 0)
				lCellGrid[i][j].setWest(lCellGrid[i - 1][j]);

			if (j > 0)
				lCellGrid[i][j].setNorth(lCellGrid[i][j - 1]);
		}
	}





	Grid<std::string> lGrid(lCellGrid[0][0]);



	std::cout << "Grid Size: [" << lGrid.getWitdh() << "," << lGrid.getHeight() << "]" << std::endl;

	for (int j = 0; j < lGrid.getHeight(); j++)
	{
		for (int i = 0; i < lGrid.getWitdh(); i++)
		{
			std::cout << "    " << lGrid.getCellValue(i, j);
		}
		std::cout << "    " << std::endl;
	}


	system("PAUSE");
	return 0;
}