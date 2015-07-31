#include "othelloArbiter.h"
#include "othelloBoard.h"

void OthelloArbiter::playOthello()
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
            //printf("Player %c has no move.\n\n", board.playerToChar(player));
        }
        else
        {
            playerCanMove[player - 1] = true;
            
            //printf("\n");
            //board.print();
            //printf("\n");

            int x, y;
            do
            {
                //printf("Player %c Choose move.\n", board.playerToChar(player));
                players_[plalyer - 1](board.getState(), board.getValidPlays(), x, y);
                //printf("Input: %d %d\n", x, y);
            }
            while(!board.play(player, x, y));
        }

        if(player == 1) player = 2;
        else player = 1;
    }

    unsigned char winner = board.winner();

    //printf("\n");
    //board.print();
    //printf("\n");

    printf("Player %c Wins!\n", board.playerToChar(winner));

    return winner;
}
