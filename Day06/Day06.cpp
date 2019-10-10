#include "inputs.h"
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cctype>
#include <utility>

int CalcManhattenDistance( const std::pair<int,int>& pt1, const std::pair<int,int>& pt2)
{
    return abs(pt1.first-pt2.first) + abs(pt1.second-pt2.second);
}

std::pair<int,int> FindMaxXandY( const std::map<std::string,std::pair<int,int>>& data)
{
    int maxX = 0;
    int maxY = 0;

    for( auto&& it : data)
    {
        auto pt = it.second;
        if ( pt.first > maxX)
            maxX = pt.first;
        if ( pt.second > maxY)
            maxY = pt.second;
    }
    return std::make_pair(maxX, maxY);
}

void PopulateGrid(const std::map<std::string,std::pair<int, int>>& data, std::vector<std::vector<std::string>*>& grid)
{
    for (auto it : data)
    {   
        auto pt = it.second;
        auto row = grid[pt.second];
        (*row)[pt.first] = it.first;
    }
}


void CalculateClosestLocations( const std::map<std::string,std::pair<int, int>>& data,std::vector<std::vector<std::string>*>& grid)
{
    for(auto y = 0; y< grid.size(); y++)
    {
        auto row = grid[y];
        for( auto x=0;x<row->size();x++)
        {
            std::set<std::string> closest;
            auto minDist = -1;
            //std::pair<int,int> pt;
            std::string label;
            for(auto i : data)
            {
                auto pt = i.second;
                auto dist = CalcManhattenDistance(std::make_pair(x,y), pt);
                label = (*grid[pt.second])[pt.first];
                for(auto& elem : label)
                    elem = tolower(elem);

                if (minDist == -1 || dist < minDist)
                {
                    minDist = dist;
                    closest.clear();
                    
                    closest.insert(label);
                }
                else if ( dist == minDist)
                    closest.insert(label);
            }

            if (closest.size() == 1)
                (*row)[x] = *(closest.begin());

        }
    }
}

int DetermineLargestArea(const std::map<std::string,std::pair<int, int>>& data,std::vector<std::vector<std::string>*>& grid)
{
    auto maxArea = 0;
    auto lastRow = grid[grid.size()-1];
    auto firstRow = grid[0];

    
    std::vector<std::string> firstColumn;
    firstColumn.reserve(grid.size());
    
    std::vector<std::string> lastColumn;
    lastColumn.reserve(grid.size());

    for(auto& i: grid)
    {
        auto first = (*i)[0];
        auto last = (*i)[firstRow->size()-1];
        firstColumn.push_back(first);
        lastColumn.push_back(last);
    }
    for(auto pt : data)
    {
        auto key = pt.first;
        for(auto& elem : key)
            elem = tolower(elem);

        auto count = std::count( firstRow->begin(), firstRow->end(), key);
        if ( count > 0)
            continue;
        count = std::count(lastRow->begin(), lastRow->end(), key);
        if( count > 0)
            continue;

        count = std::count(firstColumn.begin(), firstColumn.end(), key);
        if ( count > 0)
            continue;

        count = std::count(lastColumn.begin(), lastColumn.end(),key);
        if (count > 0)
            continue;

        auto currentMax = 0;
         for ( auto it = grid.begin()+1; it<grid.end()-1; ++it)   
         {
             currentMax += std::count((*it)->begin(), (*it)->end(), key);
         }

         if ( currentMax > maxArea)
            maxArea = currentMax;
    }

    return maxArea +1; //for the actual point
}

int main ()
{
    std::cout << "Day 6: Chronal Coordinates - Manhattan Distance" << std::endl;
    //auto data = inputs::GetData();

    std::map<std::string,std::pair<int,int>> data;
    data.insert(std::make_pair("A", std::make_pair(1,1)));
    data.insert(std::make_pair("B", std::make_pair(1,6)));
    data.insert(std::make_pair("C", std::make_pair(8,3)));
    data.insert(std::make_pair("D", std::make_pair(3,4)));
    data.insert(std::make_pair("E", std::make_pair(5,5)));
    data.insert(std::make_pair("F", std::make_pair(8,9)));
    
    auto maxValues = FindMaxXandY(data);

    std::cout << "The max Range is X: " << maxValues.first << " Y: "<< maxValues.second << std::endl;

    std::vector<std::vector<std::string>*> grid;
    grid.reserve(maxValues.second + 1);
    for (auto i =0; i<maxValues.second+1;i++)
    {
        auto vect = new std::vector<std::string>(maxValues.first+1,".");
        grid.push_back(vect);
    }

    PopulateGrid(data, grid);

    CalculateClosestLocations(data, grid);
    auto maxArea = DetermineLargestArea(data, grid);
    //clean up memory
    for(auto rit = grid.rbegin(); rit != grid.rend(); ++rit)
        delete *rit;

    std::cout << "The Max Area is: " << maxArea << std::endl;
    int blah;
    std::cin >> blah;
}