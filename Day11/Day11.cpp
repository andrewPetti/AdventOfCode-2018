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
    auto xSize = 300;
    auto ySize = 300;

    auto grid = std::vector<std::vector<int>>(300);
    //grid.reserve(300);
    for(auto y =0; y<300; y++)
    {
        for (auto x = 0; x< 300; x++)
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
        sum += grid[y][left] + grid[y][left+1] +grid[y][left+2];

    return sum;
}
std::pair<int,int> FindLargestOutputSquare(const std::vector<std::vector<int>>& grid)
{
    auto sqSize = 3;
    auto buffer = sqSize-1;

    auto maxSum = 0;
    auto coord = std::make_pair(0,0);
    auto sum = 0;
    //auto height = grid.s
    for(auto y =0; y<grid.size()-buffer; y++)
    {
        auto length = grid[y].size();
        for (auto x =0; x< length-buffer; x++)
        {
            sum =SumSquare(grid, x,y, sqSize);

            if ( sum > maxSum)
            {
                maxSum = sum;
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

    std::cout <<"Test 122,79, 57: " << CalcPowerLevelForCell(122,79,57);
    auto gridSerialNumber = 5535;
    //gridSerialNumber = 18;
    auto grid = BuildPowerGrid(gridSerialNumber);
    std:: cout << "Part 1: what is x,y coordinate for top let of the 3x3 square with laregest total power?" << std::endl;

      auto coord = FindLargestOutputSquare(grid);

    //auto coord = std::make_pair(0,0);
    std::cout << "The x, y coordinates are : " << coord.first <<","<<coord.second<<std::endl;
    std::cout << "Part 2: TBD" <<std::endl;
    for (auto i = 1; i<=300; i++)
    {
        FindLargestOutput(grid,i);
    }
    auto blah = 0;
    std::cout << "please enter a number to exit: ";
    std::cin >> blah;
    return 0;
}