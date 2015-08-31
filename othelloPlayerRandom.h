#include <random>

#include "othelloPlayer.h"

#ifndef OTHELLOPLAYERRANDOM_h
#define OTHELLOPLAYERRANDOM_h

class OthelloPlayerRandom : public OthelloPlayer
{
private:
    std::mt19937 mtRand_;
    std::uniform_int_distribution<int> randDist_;

    void returnPlay(const OthelloBoard<8, 8>&, const std::set<std::pair<int, int>>&, int&, int&);

public:
    OthelloPlayerRandom();
};

#endif
