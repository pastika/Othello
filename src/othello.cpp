#include "othelloArbiter.h"
#include "othelloPlayerRandom.h"
#include "othelloPlayerHuman.h"
#include "othelloPlayerCES.h"
#include "othelloPlayerPCEM.h"
#include "othelloPlayerLOM.h"

#include "getopt.h"

#include <ctime>

int main()
{
    //Add option parsing here

    int wins[3] = {0, 0, 0};

    OthelloPlayer *p1 = new OthelloPlayerPCEM();
    OthelloPlayer *p2 = new OthelloPlayerRandom();
    //OthelloPlayer *p2 = new OthelloPlayerHuman();

    int games = 10000;
    for(int n = 0; n < games; ++n)
    {
        OthelloArbiter oarb(0);

        oarb.setVerbosity(1);

        oarb.addPlayer(p1);
        oarb.addPlayer(p2);

        unsigned char winner = oarb.playOthello();

        if(winner == 2)
            break;
        
        wins[winner]++;
    }

    printf("\nWins:\nPlayer X: %d\nPlayer O: %d\nTies    : %d\n", wins[1], wins[2], wins[0]); 
}
