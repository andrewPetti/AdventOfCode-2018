#include <vector>

namespace inputs
{
    struct GameInfo
    {
        int numPlayers;
        int lastMarble;
        int highestScore;
    };

    std::vector<GameInfo> GetData()
    {
        std::vector<GameInfo> data;
        data.push_back( GameInfo { 463, 71787});
        return data;
    }

    std::vector<GameInfo> GetTestData()
    {
        std::vector<GameInfo> data;
        data.push_back(GameInfo{10, 1618, 8317});
        data.push_back(GameInfo{13, 7999, 146373});
        data.push_back(GameInfo{17, 1104, 2764});
        data.push_back(GameInfo{21, 6111, 54718});
        data.push_back(GameInfo{30,5807,37305});

        return data;
    }
}