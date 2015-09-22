#include "othelloPlayerCES.h"

#include <cmath>
#include <map>
#include <vector>

OthelloPlayerCES::OthelloPlayerCES() {}

void OthelloPlayerCES::returnPlay(const OthelloBoard<8, 8>& board, const std::set<std::pair<int, int>>& moves, int& x, int& y)
{
    std::map<int, std::vector<std::pair<int, int>>> plays;
    for(auto& move : moves)
    {
        if((move.first == 0 || move.first == 7) && (move.second == 0 || move.second == 7))
        {
            plays[1].push_back(move);
        }
        else if(move.first == 0 || move.first == 7 || move.second == 0 || move.second == 7)
        {
            plays[2].push_back(move);
        }
        else
        {
            plays[2 + std::max(int(abs(3.5 - move.first)), int(abs(3.5 - move.second)))].push_back(move);
        }
    }

    const auto& finalMove = plays.begin();

    x = finalMove->second.front().first;
    y = finalMove->second.front().second;
}
