#include <vector>

#include "othelloPlayer.h"

#ifndef OTHELLOARBITER_h
#define OTHELLOARBITER_h

class OthelloArbiter
{
private:
    //players list
    std::vector<OthelloPlayer*> players_;

public:
    void addPlayer(OthelloPlayer* const player) {players_.push_back(player);}
    unsigned char playOthello();
};

#endif
