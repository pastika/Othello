#include "othelloPlayer.h"

#ifndef OTHELLOPLAYERCES_h
#define OTHELLOPLAYERCES_h

class OthelloPlayerCES : public OthelloPlayer
{
private:
    void returnPlay(const OthelloBoard<8, 8>&, const std::set<std::pair<int, int>>&, int&, int&);

public:
    OthelloPlayerCES();
};

#endif
