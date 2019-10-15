
#include <cctype>
#include <iostream>
#include "Input.h"

void ReadHeader(std::vector<int>::iterator &headerPos, int &children, int &meta)
{
    children = *headerPos;
    meta = *(++headerPos);
    headerPos++;
}

int SumMeta(std::vector<int>::iterator &start, const int &meta)
{
    auto sum = 0;
    for (auto j = 0; j < meta; j++)
    {
        sum += *start;
        start++;
    }
    return sum;
}

int ProcessNode(std::vector<int>::iterator &pos, const std::vector<int>::iterator &end, const int &children, const int &meta)
{
    auto sum = 0;

    for (auto i = 0; i < children; i++)
    {
        auto innerChildren = 0;
        auto innerMeta = 0;
        ReadHeader(pos, innerChildren, innerMeta);
        sum += ProcessNode(pos, end, innerChildren, innerMeta);
    }

    sum += SumMeta(pos, meta);
    return sum;
}
int SumMetaData(std::vector<int>::iterator &start, const std::vector<int>::iterator &end)
{
    auto children = 0;
    auto meta = 0;

    ReadHeader(start, children, meta);
    auto sum = ProcessNode(start, end, children, meta);

    return sum;
}

int SumIndexedMeta(std::vector<int>::iterator &start, const int &meta, const std::vector<int> &childrenData)
{
    auto sum = 0;
    for (auto i = 0; i < meta; i++)
    {
        auto index = *start;
        if (index <= childrenData.size())
            sum += childrenData[index - 1];

        ++start;
    }
    return sum;
}
int ProcessInstructions(std::vector<int> &instructions)
{
    int sum = 0;

    auto it = instructions.begin();
    auto itEnd = instructions.end();

    sum = SumMetaData(it, itEnd);

    return sum;
}
void ProcessChildren(std::vector<int>::iterator &pos, std::vector<int> &childrenValues, const int &children, const int &meta)
{
    std::vector<int> innerChildrenValues;

    for (auto i = 0; i < children; i++)
    {
        auto innerChildren = 0;
        auto innerMeta = 0;
        ReadHeader(pos, innerChildren, innerMeta);
        ProcessChildren(pos, innerChildrenValues, innerChildren, innerMeta);
        //        if (innerChildren > 0)
        //            childrenValues.push_back(SumIndexedMeta(pos, meta, innerChildrenValues));
    }

    if (children == 0)
        childrenValues.push_back(SumMeta(pos, meta));
    else
        childrenValues.push_back(SumIndexedMeta(pos, meta, innerChildrenValues));
}

int RootNodeCalc(std::vector<int>::iterator &pos)
{

    auto children = 0;
    auto meta = 0;
    ReadHeader(pos, children, meta);
    std::vector<int> childrenValues;
    ProcessChildren(pos, childrenValues, children, meta);

    return childrenValues[0];
}

int ProcessPart2(std::vector<int> &instructions)
{
    int sum = 0;
    auto it = instructions.begin();
    sum = RootNodeCalc(it);
    return sum;
}
int main()
{
    std::cout << "Day 8: Memory Maneuver ...." << std::endl;
    std::cout << "Part 1: What is the sum of the metadata: " << std::endl;

    auto instructions = inputs::GetData();
    //instructions = inputs::GetTestData();
    std::cout << "The instructions have: " << instructions.size() << " elements!" << std::endl;

    auto it = instructions.begin();

    auto sum = ProcessInstructions(instructions);
    std::cout << "Part 1 has found the sum to be " << sum << std::endl;

    std::cout << "Part 2: Determine Root Node Value" << std::endl;

    sum = ProcessPart2(instructions);
    std::cout << "The value for the root node is: " << sum << std::endl;
    int blah;
    std::cout << "Enter a number to exit: ";
    std::cin >> blah;
}