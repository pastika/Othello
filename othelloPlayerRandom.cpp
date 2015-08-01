#include "othelloPlayerRandom.h"

OthelloPlayerRandom::OthelloPlayerRandom() : randDist_(0, 10000000), mtRand_()
{
    
}

void OthelloPlayerRandom::returnPlay(const unsigned char** const board, const std::set<std::pair<int, int>>& moves, int& x, int& y)
{
    const int nMoves = moves.size();
    const int randNum = randDist_(mtRand_);

    auto iter = moves.begin();
    for(int i = 0; i < (randNum%nMoves); ++i) ++iter;
    x = iter->first;
    y = iter->second;
}
