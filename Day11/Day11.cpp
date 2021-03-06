#include <iostream>
#include <cctype>
#include <vector>
//#include <pair>

int CalcPowerLevelForCell(const int& x, const int& y, const int& serialNumber)
{
    auto rackID = x + 10;
    auto powerLevel = rackID * y;
    powerLevel += serialNumber;
    powerLevel *= rackID;
    auto hundreds = powerLevel%1000;
    auto number = hundreds/100;

    return number -5;
}
std::vector<std::vector<int>> BuildPowerGrid(const int& serialNumber)
{
    auto xSize = 301;
    auto ySize = 301;

    auto grid = std::vector<std::vector<int>>(301);
    //grid.reserve(300);
    for(auto y =0; y<=300; y++)
    {
        for (auto x = 0; x<=300; x++)
            {
                grid[y].push_back(CalcPowerLevelForCell(x, y, serialNumber));
            }
    }
    return grid;
}

int SumSquare(const std::vector<std::vector<int>>& grid, int left, int top, int sqSize)
{
    auto sum = 0;
    for (auto y = top; y< top+sqSize;y++)
        for( auto x = left; x<left+sqSize;x++)
            sum += grid[y][x];

    return sum;
}
std::pair<int,int> FindLargestOutputSquare(const std::vector<std::vector<int>>& grid, const int& sqSize, int& maxPower)
{
    auto buffer = sqSize-1;

    //auto maxSum = 0;
    auto coord = std::make_pair(0,0);
    auto sum = 0;
    //auto height = grid.s
    for(auto y =1; y<grid.size()-buffer; y++)
    {
        auto length = grid[y].size();
        for (auto x =1; x< length-buffer; x++)
        {
            sum =SumSquare(grid, x,y, sqSize);

            if ( sum > maxPower)
            {
                maxPower = sum;
                coord.first = x;
                coord.second = y;
            }
        }
    }

    sum = SumSquare(grid,coord.first,coord.second,sqSize);
    return coord;
}
int main()
{
    std::cout << "Day 11 - chronal Charge ----" << std::endl;

    std::cout <<"Test 122,79, 57: " << CalcPowerLevelForCell(122,79,57) <<std::endl;
    auto gridSerialNumber = 5535;
    //gridSerialNumber = 18;
    auto grid = BuildPowerGrid(gridSerialNumber);
    std:: cout << "Part 1: what is x,y coordinate for top let of the 3x3 square with laregest total power?" << std::endl;
    auto maxPower = 0;
    auto coord = FindLargestOutputSquare(grid, 3, maxPower);

    //auto coord = std::make_pair(0,0);
    std::cout << "The x, y coordinates are : " << coord.first <<","<<coord.second<<std::endl;
    std::cout << "Part 2: TBD" <<std::endl;
    maxPower = -1;
    std::pair<int,int> maxCoord;
    auto maxSize = -1;
    for (auto i = 0; i<=300; i++)
    {
        auto power =0;
        coord = FindLargestOutputSquare(grid,i, power);
        if ( power > maxPower)
        {   
            maxCoord = coord;
            maxSize = i;
            maxPower = power;
        }
    }
    std::cout << "The largest power total is found x,y,size: " << maxCoord.first <<","<<maxCoord.second<<","<<maxSize<<std::endl;
    auto blah = 0;
    std::cout << "please enter a number to exit: ";
    std::cin >> blah;
    return 0;
}