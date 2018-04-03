#include "ListPrinters.h"

#include <iostream>

void PrintList(List<Cardinal> aList)
{
	for (int i = 0; i < aList.size(); i++)
	{
		switch (aList[i])
		{
		case NORTH:
			std::cout << "NORTH, ";
			break;
		case WEST:
			std::cout << "WEST, ";
			break;
		case SOUTH:
			std::cout << "SOUTH, ";
			break;
		case EAST:
			std::cout << "EAST, ";
			break;
		default:
			break;
		}
		
	}
	std::cout << std::endl;
}

