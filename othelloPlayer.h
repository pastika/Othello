#include <set>
#include <utility>

#include "othelloBoard.h"

#ifndef OTHELLOPLAYER_h
#define OTHELLOPLAYER_h

class OthelloPlayer
{
private:
    virtual void returnPlay(const OthelloBoard<8, 8>&, int&, int&) = 0;

protected:
    unsigned char player_;

public:
    inline void operator()(const OthelloBoard<8, 8>& board, int& x, int& y)
    {
        returnPlay(board, x, y);
    }

    void setPlayer(const unsigned char player)
    {
        player_ = player;
    }

    virtual void winner(const unsigned char winner, const OthelloBoard<8, 8>& board)
    {
    }
};

#endif
