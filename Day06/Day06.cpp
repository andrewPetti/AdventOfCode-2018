#include "inputs.h"
#include <iostream>

int CalcManhattenDistance( const std::pair<int,int>& pt1, const std::pair<int,int>& pt2)
{
    return abs(pt1.first-pt2.first) + abs(pt1.second-pt2.second);
}

std::pair<int,int> FindMaxXandY( const std::vector<std::pair<int,int>>& data)
{
    int maxX = 0;
    int maxY = 0;

    for( auto&& it : data)
    {
        if ( it.first > maxX)
            maxX = it.first;
        if ( it.second > maxY)
            maxY = it.second;
    }
    return std::make_pair(maxX, maxY);
}

int main ()
{
    std::cout << "Day 6: Chronal Coordinates - Manhattan Distance" << std::endl;
    auto data = inputs::GetData();

    auto maxValues = FindMaxXandY(data);

    std::cout << "The max Range is X: " << maxValues.first << " Y: "<< maxValues.second << std::endl;

    std::vector<std::vector<std::string>> grid;
    grid.reserve(maxValues.second);
    for (auto i =0; i<maxValues.first;i++)
    {
        auto vect = new std::vector<std::string>(maxValues.second,".");
        grid.push_back(vect);
    }
    int blah;
    std::cin >> blah;
}