#include <vector>

#include "othelloPlayer.h"
#include <sys/socket.h>

#ifndef OTHELLOARBITER_h
#define OTHELLOARBITER_h

class OthelloArbiter
{
private:
    //players list
    std::vector<OthelloPlayer*> players_;

    int verbosity_;
    int sockd_;

public:
    void addPlayer(OthelloPlayer* const player) {players_.push_back(player);}
    unsigned char playOthello();

    void setVerbosity(int verbosity);

    OthelloArbiter(int sockd);
};

#endif
