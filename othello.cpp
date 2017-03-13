#include "othelloArbiter.h"
#include "othelloPlayerRandom.h"
#include "othelloPlayerHuman.h"
#include "othelloPlayerCES.h"
#include "othelloPlayerLOM.h"

#include "getopt.h"

int main()
{
    //Add option parsing here

    int wins[2] = {0, 0};

    OthelloPlayer *p1 = new OthelloPlayerLOM();
    //OthelloPlayer *p2 = new OthelloPlayerRandom();
    OthelloPlayer *p2 = new OthelloPlayerHuman();

    int games = 1;
    for(int n = 0; n < games; ++n)
    {
        OthelloArbiter oarb;

        oarb.setVerbosity(1);

        oarb.addPlayer(p1);
        oarb.addPlayer(p2);

        unsigned char winner = oarb.playOthello();
        
        wins[winner - 1]++;
    }

    printf("\nWins:\nPlayer X: %d\nPlayer O: %d\n", wins[0], wins[1]); 
}
