#include "othelloArbiter.h"
#include "othelloPlayerRandom.h"
#include "othelloPlayerHuman.h"
#include "othelloPlayerCES.h"

#include "getopt.h"

int main()
{
    //Add option parsing here

    int wins[2] = {0, 0};

    OthelloPlayer *p1 = new OthelloPlayerCES();
    OthelloPlayer *p2 = new OthelloPlayerRandom();

    for(int n = 0; n < 10000; ++n)
    {
        OthelloArbiter oarb;

        oarb.setVerbosity(0);

        oarb.addPlayer(p1);
        oarb.addPlayer(p2);

        unsigned char winner = oarb.playOthello();
        
        wins[winner - 1]++;
    }

    printf("\nWins:\nPlayer X: %d\nPlayer O: %d\n", wins[0], wins[1]); 
}
