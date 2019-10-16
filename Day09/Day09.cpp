#include <algorithm>
#include <cctype>
#include <iostream>
#include "inputs.h"

int ProcessGame(const inputs::GameInfo& info)
{
    std::vector<int> gameCircle { 0, 2, 1};
    std::vector<int> players;
    players.assign(info.numPlayers,0);

    auto marbleNumber = 3;
    auto currentPlayer = 3;
    auto currentPos = gameCircle.begin();
    currentPos++; //2 is the starting current pos here
    auto score = 0;
    while( marbleNumber <= info.lastMarble)
    {
        if ( marbleNumber % 23 != 0)
        {
            //currentPos++;
            if ( currentPos+1 != gameCircle.end() )
                {
                    //currentPos +=2;
                
                    currentPos = gameCircle.insert(currentPos+2, marbleNumber);
                }
            else 
            {
                currentPos = gameCircle.begin();
                currentPos = gameCircle.insert(currentPos+1, marbleNumber);
            }
        }
        else
        {   
            auto dist = std::distance(gameCircle.begin(), currentPos);
            if ( dist > 7)
                currentPos = gameCircle.begin() += dist-7;
            else
            {
                currentPos = gameCircle.begin() += gameCircle.size() - (7-dist);
            }
            score = (*currentPos) + marbleNumber;
            //std::cout << "Last Marble: " << score << std::endl;
            players[currentPlayer-1] += score;
            //if (players[currentPlayer-1] > info.highestScore)
            //    {
            //        std::cout << "Error Highest score is too high at: " << players[currentPlayer-1] <<" and last marble was calucalted to be: "<< score <<std::endl;
            //        break;
            //    }
            currentPos = gameCircle.erase(currentPos);
        }
        
        //increment players
        if ( currentPlayer == info.numPlayers)
            currentPlayer = 1;
        else
            currentPlayer++;

        //increment marbel
        marbleNumber ++;
    }

    return *std::max_element(players.begin(), players.end());
}
int main()
{
    std::cout << "Day 9: Marble Mania " << std::endl;
    auto highScore = 0;
    auto data = inputs::GetData();
    //data = inputs::GetTestData();
    for ( auto info: data)
    {
        highScore = ProcessGame(info);
        std::cout << "For game with " << info.numPlayers << " and where the last marble is worth " << info.lastMarble << " the high score is: " << highScore <<std::endl;
    }
    highScore = 0;
    //std::cout << "The high score for the game in part 1 is:  " << highScore << std::endl;
    std::cout<< "Part 2 is what is the score if last marble is 100 times larger" << std::endl;

    for (auto info:data)
    {
        info.lastMarble *= 100;
        highScore = ProcessGame(info);
        std::cout << "For game with " << info.numPlayers << " and where the last marble is worth " << info.lastMarble << " the high score is: " << highScore <<std::endl;
    }
    std::cout<<"Please enter a number to exit: ";
    int blah;
    std::cin >> blah; 
}