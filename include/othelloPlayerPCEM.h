#include "othelloPlayer.h"

#ifndef OTHELLOPLAYERPCEM_h
#define OTHELLOPLAYERPCEM_h

class OthelloPlayerPCEM : public OthelloPlayer
{
private:
    void returnPlay(const OthelloBoard<8, 8>&, int&, int&);

public:
    OthelloPlayerPCEM();
};

#endif
