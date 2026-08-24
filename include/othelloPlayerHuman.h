#include <cstdio>

#include "othelloPlayer.h"

#ifndef OTHELLOPLAYERHUMAN_h
#define OTHELLOPLAYERHUMAN_h

class OthelloPlayerHuman : public OthelloPlayer
{
private:
    void returnPlay(const OthelloBoard<8, 8>&, int& x, int& y)
    {
        char buff[32];
        if(fgets(buff, 32, stdin))
        {
            if(sscanf(buff, "%d %d", &x, &y) != 2)
            {
                printf("Please specify 2 and only 2 numbers for x and y position.\n");
            }
        }
        else
        {
            printf("No input found.\n");
        }
    }

public:
    OthelloPlayerHuman(){};
};

#endif
