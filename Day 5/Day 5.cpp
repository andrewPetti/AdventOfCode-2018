// Day 5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "inputs.h"

#include <algorithm>
#include <iostream>
#include <cctype>

std::string ReducePolymer( std::string polymer )
{
	auto localPolymer = polymer;
	auto i = 0;
	while( i < localPolymer.length() - 1 )
	{
		auto first = localPolymer[i];
		auto second = localPolymer[i + 1];

		auto firstUpper = std::isupper( first );
		auto secondUpper = std::isupper( second );
		if( firstUpper == secondUpper )
		{
			i++;
			continue;
		}

		if( std::toupper( first ) == std::toupper( second ) )
			localPolymer.erase( i, 2 );
		else
			i++;
	}
	return localPolymer;
}

int main()
{
	std::cout << "Day 5: Investigate the Polymer ....\n";
	auto polymer = inputs::GetData();
	std::cout << "The Input Polymer is: \n " << polymer << std::endl;

	auto toReduceSize = polymer.length();
	auto resultSize = 0;

	std::string reducedPolymer;
	auto polymerToReduce = polymer;

	while( toReduceSize != resultSize )
	{
		toReduceSize = polymerToReduce.length();

		reducedPolymer = ReducePolymer( polymerToReduce );
		resultSize = reducedPolymer.length();
		polymerToReduce = reducedPolymer;
	}

	std::cout << "The final reduced polymer is: \n" << reducedPolymer << std::endl;
	std::cout << "Unit Length is: " << reducedPolymer.length();
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
