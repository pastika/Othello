#include <set>
#include <utility>

#include "othelloBoard.h"

#ifndef OTHELLOPLAYER_h
#define OTHELLOPLAYER_h

class OthelloPlayer
{
private:
    virtual void returnPlay(const OthelloBoard<8, 8>&, const std::set<std::pair<int, int>>&, int&, int&) = 0;

public:
    inline void operator()(const OthelloBoard<8, 8>& board, const std::set<std::pair<int, int>>& plays, int& x, int& y)
    {
        returnPlay(board, plays, x, y);
    }
};

#endif
