#include "othelloBoard.h"

#include <random>
#include <functional>

void playerRandom(const unsigned char** state, const std::set<std::pair<int, int>>& moves, int& x, int& y, const int randnum)
{
    int nMoves = moves.size();
    auto iter = moves.begin();
    for(int i = 0; i < (randnum%nMoves); ++i) ++iter;
    x = iter->first;
    y = iter->second;
}

void playerLeftTop(const unsigned char** state, const std::set<std::pair<int, int>>& moves, int& x, int& y)
{
    
}

void playerHuman(const unsigned char** state, const std::set<std::pair<int, int>>& moves, int& x, int& y)
{
    scanf("%d %d", &x, &y);
}

int main()
{
    //create board
    OthelloBoard<8, 8> board;

    //initialize random number generator
    std::mt19937 mtRand;
    std::uniform_int_distribution<int> randDist(0, 10000000);
    auto rand = std::bind(randDist, mtRand);

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
            printf("Player %c has no move.\n\n", board.playerToChar(player));
        }
        else
        {
            playerCanMove[player - 1] = true;
            
            printf("\n");
            board.print();
            printf("\n");

            int x, y;
            do
            {
                printf("Player %c Choose move.\n", board.playerToChar(player));
                switch(player)
                {
                case 1:
                    //Run player 1 AI
                    playerRandom(board.getState(), board.getValidPlays(), x, y, rand());
                    break;
                case 2:
                    //Run player 2 AI
                    playerHuman(board.getState(), board.getValidPlays(), x, y);
                    break;
                default:
                    printf("WTF?? Player not defined\n");
                    break;
                }
                //board.getFirstPlay(x, y);
                //num = 2;
                printf("Input: %d %d\n", x, y);
            }
            while(!board.play(player, x, y));
        }

        if(player == 1) player = 2;
        else player = 1;
    }

    unsigned char winner = board.winner();

    printf("\n");
    board.print();
    printf("\n");

    printf("Player %c Wins!\n", board.playerToChar(winner));
}
