#include "othelloPlayer.h"
#include <sys/socket.h>

#include <memory>

#ifndef OTHELLOARBITERCLIENT_H
#define OTHELLOARBITERCLIENT_H

class OthelloArbiterClient
{
private:
    int sockd_;
    int verbosity_;

    std::unique_ptr<OthelloPlayer> player_;
    
public:
    OthelloArbiterClient(int sockd);

    void setPlayer(OthelloPlayer* player);

    void setVerbosity(int verbosity);

    void beginArbitration();
};

#endif
