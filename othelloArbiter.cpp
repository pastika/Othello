#include "othelloArbiter.h"
#include "othelloBoard.h"

unsigned char OthelloArbiter::playOthello()
{
    //create board
    OthelloBoard<8, 8> board;

    //Basic game arbiter     
    int playerCanMove[2];
    playerCanMove[0] = true;
    playerCanMove[1] = true;
    for(unsigned char player = 1; playerCanMove[0] || playerCanMove[1]; player = ((player == 1)?2:1))
    {
        if(!board.avaliableMoves(player))
        {
            playerCanMove[player - 1] = false;
            if(verbosity_ >= 1) printf("Player %s has no move.\n\n", board.playerToCharAndColor(player));
        }
        else
        {
            playerCanMove[player - 1] = true;
            
            if(verbosity_ >= 1) 
            {
                printf("\n");
                board.print();
                printf("\n");

            }

            int x, y;
            do
            {
                if(verbosity_ >= 1) printf("Player %s Choose move.\n", board.playerToCharAndColor(player));
                (*players_[player - 1])(board.getState(), x, y);
            }
            while(!board.play(player, x, y));

            if(verbosity_ >= 1) printf("Input: %d %d\n", x, y);
        }
    }

    unsigned char winner = board.winner();

    if(verbosity_ >= 1) 
    {
        printf("\n");
        board.print();
        printf("\n");
    }

    if(verbosity_ >= 0) printf("Player %c Wins!\n", board.playerToChar(winner));

    return winner;
}

void OthelloArbiter::setVerbosity(int verbosity)
{
    verbosity_ = verbosity;
}

OthelloArbiter::OthelloArbiter(int sockd)
{
    verbosity_ = 0;
    sockd_ = sockd;
}
