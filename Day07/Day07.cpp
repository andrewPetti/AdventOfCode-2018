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

void FindInitialCandidates(const std::map<char, std::set<char>> &depMap, std::set<char> &candidates)
{
    char letter = 'A';
    for (auto i = 0; i < 26; i++, letter++)
    {
        if (depMap.find(letter) == depMap.end())
            candidates.insert(letter);
    }
}
void DetermineOrderBasedOnDependencies(const std::map<char, std::set<char>> &dependMap, std::string &buildOrder)
{
    auto localMap = dependMap;

    std::set<char> candidates;

    FindInitialCandidates(localMap, candidates);

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

bool AssignTask(const int &currentTime, const char &task, std::vector<int> &finishTimes, std::vector<char> &processing)
{
    auto basicTime = 60;

    for (auto i = 0; i < finishTimes.size(); i++)

        if (finishTimes[i] < currentTime)
        {
            processing[i] = task;
            finishTimes[i] = currentTime + basicTime + task - 'A';
            return true;
        }

    return false;
}

void CleanUpMapAndFindNext(const int &currentTime, const std::vector<int> &finishTimes, std::vector<char> &currentSteps, std::map<char, std::set<char>> &theMap, std::set<char> &candidates)
{
    std::set<char> toRemove;
    for (auto i = 0; i < finishTimes.size(); i++)
    {
        if (finishTimes[i] == currentTime - 1 && currentSteps[i] != '\0')
        {
            toRemove.insert(currentSteps[i]);
            currentSteps[i] = '\0';
        }
    }

    for (auto remove : toRemove)
        ProcessStep(remove, theMap, candidates);
}

bool AreAllWorkersDone(const std::vector<char> &steps)
{
    for (auto i : steps)
    {
        if (i != '\0')
            return false;
    }

    return true;
}
int DetermineTime(const std::map<char, std::set<char>> &dependMap)
{
    auto localMap = dependMap;

    std::set<char> candidates;
    FindInitialCandidates(localMap, candidates);

    auto currentTime = 0;
    std::vector<int> finishTimes{-1, -1, -1, -1, -1};
    std::vector<char>
        processingStep(5);

    auto done = false;

    while (!done)
    {
        CleanUpMapAndFindNext(currentTime, finishTimes, processingStep, localMap, candidates);

        auto it = candidates.begin();
        if (it != candidates.end())
        {
            for (auto j = 0; j < 5; j++)
            {
                if (AssignTask(currentTime, *it, finishTimes, processingStep))
                {
                    it = candidates.erase(it);
                    if (it == candidates.end())
                        break;
                }
            }
        }

        if (AreAllWorkersDone(processingStep))
            done = true;
        else
            currentTime++;
    }

    //    auto max = std::max_element(finishTimes.begin(), finishTimes.end());

    //  return *max;
    return currentTime;
}

int main()
{
    std::cout << "Day 7: The Sum of Its Parts ...." << std::endl;
    std::cout << "Part 1: What is the order to assemble: " << std::endl;

    auto instructions = inputs::GetData();
    /*instructions = std::vector<std::string>{
        "Step C must be finished before step A can begin.",
        "Step C must be finished before step F can begin.",
        "Step A must be finished before step B can begin.",
        "Step A must be finished before step D can begin.",
        "Step B must be finished before step E can begin.",
        "Step D must be finished before step E can begin.",
        "Step F must be finished before step E can begin."}; */
    //	std::cout << "The Input Polymer is: \n " << polymer << std::endl;
    std::map<char, std::set<char>> dependMap;

    BuildDependencies(instructions, dependMap);
    auto s = dependMap.size();
    std::cout << "Part 1 has found " << s << " steps so far!" << std::endl;

    std::string buildOrder;
    DetermineOrderBasedOnDependencies(dependMap, buildOrder);
    std::cout << "The build order is: " << buildOrder << std::endl;
    std::cout << "Part 2: How Long to build?" << std::endl;
    auto time = DetermineTime(dependMap);
    std::cout << "The time to build is: " << time << std::endl;
}