// Dec 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "boost\algorithm\string.hpp"
#include <map>

#include "inputs.h"

struct lineData
{
	std::string id;
	int xStart;
	int yStart;
	int xLength;
	int yLength;
};

lineData ParseLine( std::string& line )
{
	auto delim1 = "@";
	auto delim2 = ":";
	auto pos1 = line.find( delim1 );
	auto pos2 = line.find( delim2 );
	auto id = line.substr( 1, pos1 );
	auto idNum = std::stoi( id );
	auto gridPos = line.substr( pos1 + 1, ( pos2 - pos1 ) - 1 );
	auto rectSize = line.substr( pos2 + 1, line.size() - pos2 + 1 );

	boost::trim( gridPos );
	auto split = gridPos.find( "," );
	auto xPos = gridPos.substr( 0, split );
	boost::trim( xPos );

	auto yPos = gridPos.substr( split + 1, gridPos.size() - split + 1 );
	boost::trim( yPos );

	boost::trim( rectSize );
	auto xSplit = rectSize.find( "x" );

	auto xSize = rectSize.substr( 0, xSplit );
	boost::trim( xSize );

	auto ySize = rectSize.substr( xSplit + 1, rectSize.size() - xSplit + 1 );
	boost::trim( ySize );

	lineData parsedData;
	parsedData.xStart = std::stoi( xPos );
	parsedData.yStart = std::stoi( yPos );
	parsedData.id = id;
	parsedData.xLength = std::stoi( xSize );
	parsedData.yLength = std::stoi( ySize );

	return parsedData;
}

int main()
{
	std::cout << "Dec 3rd: Cutting the fabric \n";

	std::vector<std::vector<char>> grid( 1000, std::vector<char>( 1000, '.' ) );


	for( auto val : inputs::data )
	{
		auto line = boost::trim_copy( val );

		auto parsed = ParseLine( line );


		for( int y = parsed.yStart; y <= parsed.yStart + parsed.yLength - 1; ++y )
		{
			for( int x = parsed.xStart; x <= parsed.xStart + parsed.xLength - 1; ++x )
			{
				if( grid[y][x] == '.' )
					grid[y][x] = '#';
				else
					grid[y][x] = 'X';
			}
		}
	}

	auto overlap = 0;
	for( auto row : grid )
	{
		overlap += std::count( row.begin(), row.end(), 'X' );
	}

	std::cout << "Overlap in square inches is: " << overlap;
	auto count = 0;
	std::string foundID;
	for( auto val : inputs::data )
	{
		auto trimmedLine = boost::trim_copy( val );
		auto parsed = ParseLine( trimmedLine );
		auto overlapped = false;

		for( int y = parsed.yStart; y <= parsed.yStart + parsed.yLength - 1 && overlapped == false; y++ )
		{
			for( int x = parsed.xStart; x <= parsed.xStart + parsed.xLength - 1; x++ )
			{
				if( grid[y][x] == 'X' )
				{
					overlapped = true;
					break;
				}
			}
		}

		if( overlapped == false )
		{
			foundID = parsed.id;
			break;
		}

	}

	std::cout << "\nThe rect that is unique has an id of: " << foundID;
	std::cout << "\n\n";
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
