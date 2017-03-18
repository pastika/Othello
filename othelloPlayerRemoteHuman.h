#include <cstdio>
#include <sys/socket.h>

#include "othelloPlayer.h"

#ifndef OTHELLOPLAYERREMOTEHUMAN_h
#define OTHELLOPLAYERREMOTEHUMAN_h

class OthelloPlayerRemoteHuman : public OthelloPlayer
{
private:
    int sockd_;

    void returnPlay(const OthelloBoard<8, 8>& board, int& x, int& y)
    {
        auto theStr = board.packageBoard();
        
        int msgLen = theStr.size();
        int byteSent = 0;
        while(msgLen - byteSent)
        {
            if( (byteSent += send(sockd_, theStr.c_str() + byteSent, msgLen, 0)) == -1)
            {
                perror("send");
            }
        }

        const int BUFLEN = 16;
        char buff[BUFLEN];
        int len;
        printf("Waiting\n");
        if( (len = recv(sockd_, buff, BUFLEN - 1, 0)) >= 1 )
        {
            buff[len] = '\0';
            printf("%s\n", buff);
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
