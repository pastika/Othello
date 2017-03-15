#include <cstdio>
#include <sys/socket.h>

#include "othelloPlayer.h"

#ifndef OTHELLOPLAYERREMOTEHUMAN_h
#define OTHELLOPLAYERREMOTEHUMAN_h

class OthelloPlayerRemoteHuman : public OthelloPlayer
{
private:
    int sockd_;

    void returnPlay(const OthelloBoard<8, 8>&, int& x, int& y)
    {
        const int BUFLEN = 32;
        char buff[BUFLEN];
        if (send(sockd_, "Select Move\n", 12, 0) == -1)
        {
            perror("send");
        }

        if( recv(sockd_, buff, BUFLEN - 1, 0) >= 1)
        {
            if(sscanf(buff, "%d %d", &x, &y) != 2)
            {
                printf("Please specify 2 and only 2 numbers for x and y position.\n");
            }
        }
        else
        {
            perror("recv");
            printf("No input found.\n");
        }
    }

public:
    OthelloPlayerRemoteHuman(int sockd)
    {
        sockd_ = sockd;
    }
};

#endif
