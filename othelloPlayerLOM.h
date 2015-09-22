#include "othelloPlayer.h"

#ifndef OTHELLOPLAYERLOM_h
#define OTHELLOPLAYERLOM_h

class OthelloPlayerLOM : public OthelloPlayer
{
private:
    void returnPlay(const OthelloBoard<8, 8>&, int&, int&);

public:
    OthelloPlayerLOM();
};

#endif
