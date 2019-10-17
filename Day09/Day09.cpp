#include <algorithm>
#include <cctype>
#include <iostream>
#include "inputs.h"
#include <list>


template<typename Iter>
void circular_inc(Iter first, Iter last, int inc, Iter& it)
{
    while (inc--) {
        if (it == last)
            it = first;
        ++it;
    }
}

template<typename Iter>
void circular_dec(Iter first, Iter last, int dec, Iter& it)
{
    while (dec++) {
        if (it == first)
            it = last;
        --it;
    }
}

uint64_t ProcessGame(const inputs::GameInfo& info)
{
    std::list<int> gameCircle { 0, 2, 1};
    std::vector<uint64_t> players;
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
            circular_inc(std::begin(gameCircle), std::end(gameCircle), 2, currentPos);
            currentPos = gameCircle.insert(currentPos, marbleNumber);
        }
        else
        {   
            circular_dec(std::begin(gameCircle), std::end(gameCircle), -7, currentPos);
            
            players[currentPlayer-1] += marbleNumber + *currentPos;
            currentPos = gameCircle.erase(currentPos);
        }
        
        //increment players
        if ( currentPlayer == info.numPlayers)
            currentPlayer = 1;
        else
            currentPlayer++;

        if (marbleNumber % 500000 == 0)
            std::cout << "Just finished marble another 500,000"<< std::endl;
        //increment marbel
        marbleNumber ++;

    }

    return *std::max_element(players.begin(), players.end());
}

uint64_t play_marbles(int num_players, int marbles)
{
    int marble = 0;
    std::list<int> circle {marble};
    std::vector<uint64_t> scores (num_players, 0);
    size_t player_i = 0;

    auto it = std::begin(circle);
    while (marble < marbles) {
        ++marble;

        if (marble % 23 == 0) {
            circular_dec(std::begin(circle), std::end(circle), -7, it);
            scores[player_i] += marble + *it;
            it = circle.erase(it);
        } else {
            circular_inc(std::begin(circle), std::end(circle), 2, it);
            it = circle.insert(it, marble);
        }

        ++player_i;
        player_i %= num_players;
    }

    return *std::max_element(std::begin(scores), std::end(scores));
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
        auto score = ProcessGame(info);
        std::cout << "For game with " << info.numPlayers << " and where the last marble is worth " << info.lastMarble << " the high score is: " << score <<std::endl;
    }

    // auto answer = play_marbles(data[0].numPlayers, data[0].lastMarble*100);
    // sdd::cout << "From GitHub the answer to part 2 is : " <<answer;
    std::cout<<"Please enter a number to exit: ";
    int blah;
    std::cin >> blah; 
}