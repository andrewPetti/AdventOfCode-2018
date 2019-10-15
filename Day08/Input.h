#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

namespace inputs
{

std::vector<int> GetData()
{
    auto name = "inputSource.txt";
    std::vector<int> result;
    std::ifstream input(name);
    std::string lineData;

    while (getline(input, lineData))
    {
        int d;
        std::stringstream lineStream(lineData);

        while (lineStream >> d)
            result.push_back(d);
    }

    return result;
}

std::vector<int> GetTestData() { return std::vector<int>{2, 3, 0, 3, 10, 11, 12, 1, 1, 0, 1, 99, 2, 1, 1, 2}; }
} // namespace inputs