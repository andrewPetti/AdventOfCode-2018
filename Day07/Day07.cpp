#include <iostream>
#include <map>
#include <set>
#include <utility>

#include "inputs.h"

void BuildDependencies(const std::vector<std::string> &data, std::map<char, std::set<char>> &dependencies)
{
    //std::map<char, std::set<char> *>* dependencies = new std::map<char, std::set<char> *>();
    for (auto it : data)
    {
        auto step = it.at(36);
        auto dependency = it[5];

        auto pos = dependencies.find(step);
        if (pos == dependencies.end())
        {
            std::set<char> temp{dependency};
            dependencies.insert(make_pair(step, temp));
            //dependencies.insert(make_pair(step, newSet));
        }
        else
        {
            pos->second.insert(dependency);
        }
    }

    //return dependencies;
}

void ProcessStep(const char &toProcess, std::map<char, std::set<char>> &theMap, std::set<char> &candidates)
{
    auto it = theMap.begin();
    while (it != theMap.end())
    //for (auto it : theMap)
    {
        if (it->second.size() > 0)
        {
            it->second.erase(toProcess);
            if (it->second.size() == 0)
            {
                candidates.insert(it->first);
            }
        }
        it++;
    }
}
void DetermineOrderBasedOnDependencies(const std::map<char, std::set<char>> &dependMap, std::string &buildOrder)
{
    auto localMap = dependMap;

    std::set<char> candidates;
    char letter = 'A';
    for (auto i = 0; i < 26; i++, letter++)
    {
        if (localMap.find(letter) == localMap.end())
            candidates.insert(letter);
    }

    auto it = candidates.begin();
    while (it != candidates.end())
    {
        //if (it == candidates.end())
        //   return;

        std::string charStr;
        auto toProcess = *it;
        charStr = *it;
        buildOrder.append(charStr);
        candidates.erase(it);

        ProcessStep(toProcess, localMap, candidates);
        it = candidates.begin();
    }
    //process the char
}
int main()
{
    std::cout << "Day 7: The Sum of Its Parts ...." << std::endl;
    std::cout << "Part 1: What is the order to assemble: " << std::endl;

    auto instructions = inputs::GetData();
    //	std::cout << "The Input Polymer is: \n " << polymer << std::endl;
    std::map<char, std::set<char>> dependMap;

    BuildDependencies(instructions, dependMap);
    auto s = dependMap.size();
    std::cout << "Part 1 has found " << s << " steps so far!" << std::endl;

    std::string buildOrder;
    DetermineOrderBasedOnDependencies(dependMap, buildOrder);
    std::cout << "The build order is: " << buildOrder << std::endl;
    std::cout << "Part 2: TBD!" << std::endl;
}