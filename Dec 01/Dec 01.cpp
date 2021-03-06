// Dec 01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "Inputs.h"
#include <set>

int main()
{
    std::cout << "2018 Dec 1: Frequency Drift\n";

	auto drift = 0;
	
	for (auto const& val : inputs::data)
		drift += val;

	std::cout << "Drift is " << drift;

	std::cout << "\n\nPart two: Find repeated frequency \n";

	std::set<int> found;
	auto search = true;
	auto pos = 0;
	auto size = inputs::data.size();
	auto freq = 0;
	found.insert(freq);
	auto repeated = 0;

	while (search)
	{
		if (pos >= size)
			pos = 0;

		freq += inputs::data.at(pos);
		auto result = found.insert(freq);
		if (result.second == false)
		{
			search = false;
			repeated = freq;
		}
		
		pos++;
	}

	std::cout << "The first repeated frequency is: " << repeated;
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
