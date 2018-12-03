// Dec 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "boost\algorithm\string.hpp"
#include <map>

#include "inputs.h"

struct myRect
{
	myRect(int x, int y, int width, int height) {
		m_X = x;
		m_Y = y;
		m_Width = width;
		m_Height = height;
	}

	int m_X;
	int m_Y;
	int m_Width;
	int m_Height;

};

int main()
{
    std::cout << "Dec 3rd: Cutting the fabric \n";

	std::vector<std::vector<char>> grid(1000, std::vector<char>(1000, '.'));

	std::map<int, myRect> rects;
	for (auto val : inputs::data)
	{
		auto line = boost::trim_copy(val);

		auto delim1 = "@";
		auto delim2 = ":";
		auto pos1 = line.find(delim1);
		auto pos2 = line.find(delim2);
		auto id = line.substr(1, pos1);
		auto idNum = std::stoi(id);
		auto gridPos = line.substr(pos1 + 1, (pos2 -pos1)- 1);
		auto rectSize = line.substr(pos2 + 1, line.size() - pos2 +1);

		boost::trim(gridPos);
		auto split = gridPos.find(",");
		auto xPos = gridPos.substr(0, split);
		boost::trim(xPos);
	
		auto yPos = gridPos.substr(split + 1, gridPos.size() - split +1);
		boost::trim(yPos);

		boost::trim(rectSize);
		auto xSplit = rectSize.find("x");
	
		auto xSize = rectSize.substr(0, xSplit);
		boost::trim(xSize);
		
		auto ySize = rectSize.substr(xSplit + 1, rectSize.size() - xSplit +1);
		boost::trim(ySize);

		auto xStart = std::stoi(xPos);
		auto yStart = std::stoi(yPos);

		auto xLength = std::stoi(xSize);
		auto yLength = std::stoi(ySize);

		
		for (int y = yStart; y <= yStart + yLength-1; ++y)
		{
			for (int x = xStart; x <= xStart + xLength-1; ++x)
			{
				if ( grid[y][x] == '.' )
					grid[y][x] = '#';
				else 
					grid[y][x] = 'X';
			}
		}

		myRect rect(xStart, yStart, xLength, yLength);
		rects.insert( std::pair<int, myRect>(idNum, rect));
	}

	auto overlap = 0;
	for (auto row : grid)
	{
		overlap += std::count(row.begin(), row.end(), 'X');
	}

	std::cout << "Overlap in square inches is: " << overlap;
	auto count =0;
	std::string foundID;
	for (auto it = rects.begin(); it != rects.end(); ++it)
	{
		count++;
		auto testRect = it->second;
		auto intersect = false;
		//std::string id1 = it->first;
		std::map<int, myRect>::reverse_iterator rit;
		for (rit = rects.rbegin(); rit != rects.rend(); ++rit);
		{
			//std::string id2 = rit->first;
			if (it->first == rit->first)
				break;




			auto compareRect = rit->second;;
			auto overX = false;
			if ((testRect.m_X >= compareRect.m_X && testRect.m_X <= compareRect.m_X + compareRect.m_Width - 1) || (testRect.m_X + testRect.m_Width - 1 >= compareRect.m_X && testRect.m_X + testRect.m_Width - 1 <= compareRect.m_X + compareRect.m_Width - 1))
				overX = true;

			auto overY = false;
			if ((testRect.m_Y >= compareRect.m_Y && testRect.m_Y <= compareRect.m_Y + compareRect.m_Width - 1) || (testRect.m_Y + testRect.m_Width - 1 >= compareRect.m_Y && testRect.m_Y + testRect.m_Width - 1 <= compareRect.m_Y + compareRect.m_Width - 1))
				overY = true;

			if (overX && overY)
			{
				intersect = true;
				break;
			}
		}

		if (intersect == false)
		{
			foundID = it->first;
			break;
		}
	}

	std::cout << "The rect that is unique is : " << foundID;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
