#include <cstdio>
#include <string>
#include <utility>
#include <sys/socket.h>

#include "othelloPlayer.h"

#ifndef OTHELLOPLAYERREMOTE_h
#define OTHELLOPLAYERREMOTE_h

class OthelloPlayerRemote : public OthelloPlayer
{
private:
    int sockd_;

    void returnPlay(const OthelloBoard<8, 8>& board, int& x, int& y)
    {
        auto theStr = "play ; " + std::to_string(player_) + " ; "  + board.packageBoard();
        
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
    OthelloPlayerRemote(int sockd)
    {
        sockd_ = sockd;
    }

    void winner(const unsigned char winner, const OthelloBoard<8, 8>& board)
    {
        char buf[32];
        sprintf(buf, "winner: %hhu ; %hhu ; ", winner, player_);

        auto boardPack = std::string(buf) + board.packageBoard();

        if( send(sockd_, boardPack.c_str(), boardPack.size(), 0) == -1)
        {
            perror("send");
        }
    }
};

#endif
