#include "othelloPlayerCES.h"

#include <cmath>
#include <map>
#include <vector>

OthelloPlayerCES::OthelloPlayerCES() {}

void OthelloPlayerCES::returnPlay(const OthelloBoard<8, 8>& board, int& x, int& y)
{
    std::map<int, std::vector<std::pair<int, int>>> plays;
    for(auto& move : board.getValidPlays())
    {
        if((move.first == 0 || move.first == 7) && (move.second == 0 || move.second == 7))
        {
            plays[1].push_back(move);
        }
        else if(move.first == 0 || move.first == 7 || move.second == 0 || move.second == 7)
        {
            plays[2 + std::min(int(abs(3.5 - move.first)), int(abs(3.5 - move.second)))].push_back(move);
        }
        else
        {
            plays[5 + 4*std::max(int(abs(3.5 - move.first)), int(abs(3.5 - move.second))) + std::min(int(abs(3.5 - move.first)), int(abs(3.5 - move.second)))].push_back(move);
        }
    }
    
    x = plays.begin()->second.front().first;
    y = plays.begin()->second.front().second;
}
