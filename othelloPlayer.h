#include <set>
#include <utility>

#include "othelloBoard.h"

#ifndef OTHELLOPLAYER_h
#define OTHELLOPLAYER_h

class OthelloPlayer
{
private:
    virtual void returnPlay(const OthelloBoard<8, 8>&, int&, int&) = 0;

public:
    inline void operator()(const OthelloBoard<8, 8>& board, int& x, int& y)
    {
        returnPlay(board, x, y);
    }
};

#endif
