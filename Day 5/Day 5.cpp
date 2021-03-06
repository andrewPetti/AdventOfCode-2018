
// Day 5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "inputs.h"

#include <algorithm>
#include <iostream>
#include <cctype>

std::string ReducePolymerSinglePass(const std::string &polymer)
{
	auto localPolymer = polymer;
	auto i = 0;
	while (i < localPolymer.length() - 1)
	{
		auto first = localPolymer[i];
		auto second = localPolymer[i + 1];

		auto firstUpper = std::isupper(first);
		auto secondUpper = std::isupper(second);
		if (firstUpper == secondUpper)
		{
			i++;
			continue;
		}

		if (std::toupper(first) == std::toupper(second))
			localPolymer.erase(i, 2);
		else
			i++;
	}
	return localPolymer;
}

std::string ReducePolymer(const std::string &polymer)
{
	auto toReduceSize = polymer.length();
	auto resultSize = 0;

	std::string reducedPolymer;
	auto polymerToReduce = polymer;

	while (toReduceSize != resultSize)
	{
		toReduceSize = polymerToReduce.length();

		reducedPolymer = ReducePolymerSinglePass(polymerToReduce);
		resultSize = (int)reducedPolymer.length();
		polymerToReduce = reducedPolymer;
	}

	return reducedPolymer;
}

std::string RemoveUnit(const std::string &polymer, const char &unitToRemove)
{
	auto cleanedPolymer = polymer;
	auto i = 0;
	while (i < cleanedPolymer.length())
	{
		auto unit = cleanedPolymer[i];
		if (std::toupper(unit) == std::toupper(unitToRemove))
			cleanedPolymer.erase(i, 1);
		else
			i++;
	}

	return cleanedPolymer;
}
int main()
{
	std::cout << "Day 5: Investigate the Polymer ....\n";
	auto polymer = inputs::GetData();
	//	std::cout << "The Input Polymer is: \n " << polymer << std::endl;

	auto reducedPolymer = ReducePolymer(polymer);

	std::cout << "The part final reduced polymer has a length of: " << reducedPolymer.length() << std::endl;
	auto minLength = reducedPolymer.length();
	char problemUnit;

	auto unitToRemove = 'a';
	for (auto i = 0; i < 26; i++)
	{
		std::cout << "Cleaning polymer: " << unitToRemove << std::endl;
		auto cleanedPolymer = RemoveUnit(polymer, unitToRemove);

		auto reducedPolymer = ReducePolymer(cleanedPolymer);
		if (reducedPolymer.length() < minLength)
		{
			minLength = reducedPolymer.length();
			problemUnit = unitToRemove;
		}

		unitToRemove++;
	}

	std::cout << "The answer for part 2 is to remove the unit: " << problemUnit << " which results in a reduced size of: " << minLength << std::endl;
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
