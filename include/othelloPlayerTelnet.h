#include <cstdio>
#include <string>
#include <utility>
#include <sstream>

#include <sys/socket.h>

#include "othelloPlayer.h"

#ifndef OTHELLOPLAYERTELNET_h
#define OTHELLOPLAYERTELNET_h

class OthelloPlayerTelnet : public OthelloPlayer
{
private:
    int sockd_;

    void returnPlay(const OthelloBoard<8, 8>& board, int& x, int& y)
    {
        std::stringstream dstr;
        board.constructDisplayString(dstr);
        dstr << "\nSelect play for player " << board.playerToCharAndColor(player_) << "\n";

        int msgLen = dstr.str().size();
        int byteSent = 0;
        while(msgLen - byteSent)
        {
            if( (byteSent += send(sockd_, dstr.str().c_str() + byteSent, msgLen, 0)) == -1)
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
    OthelloPlayerTelnet(int sockd)
    {
        sockd_ = sockd;
    }

    void winner(const unsigned char winner, const OthelloBoard<8, 8>& board)
    {
        std::stringstream dstr;
        dstr << "Winner: " << board.playerToCharAndColor(player_) << "\n\n";
        board.constructDisplayString(dstr);

        int msgLen = dstr.str().size();
        int byteSent = 0;
        while(msgLen - byteSent)
        {
            if( (byteSent += send(sockd_, dstr.str().c_str() + byteSent, msgLen, 0)) == -1)
            {
                perror("send");
            }
        }
    }
};

#endif
