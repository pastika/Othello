#include "othelloArbiter.h"
#include "othelloBoard.h"

unsigned char OthelloArbiter::playOthello()
{
    //create board
    OthelloBoard<8, 8> board;

    //Basic game arbiter     
    unsigned char player = 1;
    int playerCanMove[2];
    playerCanMove[0] = true;
    playerCanMove[1] = true;
    for(;playerCanMove[0] || playerCanMove[1];)
    {
        if(!board.avaliableMoves(player))
        {
            playerCanMove[player - 1] = false;
            if(verbosity_ >= 1) printf("Player %c has no move.\n\n", board.playerToChar(player));
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
                if(verbosity_ >= 1) printf("Player %c Choose move.\n", board.playerToChar(player));
                (*players_[player - 1])(board.getState(), board.getValidPlays(), x, y);
                if(verbosity_ >= 1) printf("Input: %d %d\n", x, y);
            }
            while(!board.play(player, x, y));
        }

        if(player == 1) player = 2;
        else player = 1;
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

OthelloArbiter::OthelloArbiter()
{
    verbosity_ = 0;
}
