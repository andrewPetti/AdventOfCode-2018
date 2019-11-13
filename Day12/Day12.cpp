#include "inputs.h"
#include <iostream>
#include <cctype>
#include <vector>


std::vector<char> GetStateAfterXGenerations(const std::vector<char>& initialState, int generations  )
{
    int zeroPos = 0;
    auto instructions = inputs::GetInstructions();
    std::vector<char> nextGen;
    nextGen.reserve(initialState.size());

    for(int i = 0; i< initialState.size(); i++)
    {
        std::string key = "";
        if( i == 0)
        {
            key = ".." + std::string(initialState[i]) + std::string(initialState[i+1]) +std::string( initialState[i+2]);
            nextGen[i] = instructions.find(key)->second;
        }
        else if (i == 1)
        {
            key = "."+ initialState[i-1] + initialState[i] + initialState[i+1] + initialState[i+2];
            nextGen[i]= instructions.find(key)->second;
        }
        else if (i-initialState.size() < 3)
        {
            if ( i-initialState.size() == 2)
            {
                key = initialState[i-2]+initialState[i-1] + initialState[i] + initialState[i+1] + ".";
            }
            else
            {
                key = initialState[i-2]+initialState[i-1] + initialState[i] + "..";
            }

            nextGen[i] = instructions.find(key)->second;
        }
        else
        {
            key = initialState[i-2] + initialState[i-1] + initialState[i]+ initialState[i+1] + initialState[i+2];
            nextGen[i]= instructions.find(key)->second;
        }

    }

    return nextGen;
}

int main()
{
    std::cout <<"Day 12 - Subterranean Sustainability " << std::endl;
    
    auto initialState = inputs::GetInitialState();
    initialState = inputs::GetInitalTestState();

    auto generations = 20;
    auto finalState = GetStateAfterXGenerations( initialState, generations);
    std::cout << "FinalState is: " << std::endl ;
    for (auto i = 0; i< finalState.size(); i++)
        std::cout << finalState[i] ;
    
    std::cout << std::endl;

    auto blah = 0;
    std::cout << "please enter a number to exit: ";
    std::cin >> blah;

    return 0;
}