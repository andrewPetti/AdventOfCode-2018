// Dec 2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "inputs.h"
#include <string>
#include <set>

std::size_t FindLetter(std::string& letter, std::string& source)
{
	return source.find(letter);
}

int main()
{
	std::vector<std::string> testdata{
	   "abcdef",
		"bababc", 
		"abbcde",
		"abcccd" ,
		"aabcdd", 
		"abcdee", 
		"ababab" };
	std::cout << "Dec 2nd: The missing boxes\n";

	auto two = 0;
	auto three = 0;
	for (auto val : inputs::data)
	{
		auto length = val.size();
		auto foundTwo = 0;
		auto foundThree = 0;
		std::set<std::string> foundLetters;
		for (std::size_t i = 0; i < length-1; i++)
		{

			std::string letter(1, val[i]);
			auto result = foundLetters.insert(letter);
			auto stop = result.second ? false : true;

			auto count = 1;
			auto pos = i;
			while (stop == false)
			{
				auto src = val.substr(pos + 1, length - 1);
				auto found = FindLetter(letter, src);
				if (found == std::string::npos)
					stop = true;
				else
				{
					count++;
					pos += found +1;
				}
			}
			if (count == 2)
				foundTwo++;
			if (count == 3)
				foundThree++;
		}
		if (foundTwo > 0)
			two++;
		if (foundThree > 0)
			three++;
	}

	auto checkSum = two * three;

	std::cout << "CheckSum of the inputs is: " << checkSum;

	std::size_t pos = 0;
	std::string common;
	auto stop = false;
	for (auto val : inputs::data)
	{
		pos++;
		if (stop == true)
			break;

		for (auto it = inputs::data.begin() + pos; it != inputs::data.end(); ++it)
		{
			auto differences = 0;
			for (auto i = 0; i < (int)val.size(); ++i)
			{
				if (val[i] != (*it)[i])
					++differences;
			}
			if (differences == 1)
			{
				for (auto i = 0; i < (int)val.size(); ++i)
				{
					if (val[i] != (*it)[i])
					{
						common = val;
						common.erase(i, 1);
					}
				}

				stop = true;
				break;
			}
		}
	}

	std::cout << "The common letters of the two boxes is: " << common;

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
