#include <random>

#include "othelloPlayer.h"

#ifndef OTHELLOPLAYERRANDOM_h
#define OTHELLOPLAYERRANDOM_h

class OthelloPlayerRandom : public OthelloPlayer
{
private:
    std::mt19937 mtRand_;
    std::uniform_int_distribution<int> randDist_;

    void returnPlay(const OthelloBoard<8, 8>&, int&, int&);

public:
    OthelloPlayerRandom(int seed = 12321);
};

#endif
