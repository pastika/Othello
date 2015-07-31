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
    x = moves.begin()->first;
    y = moves.begin()->second;
}

void playerCornerEdgeRand(const unsigned char** state, const std::set<std::pair<int, int>>& moves, int& x, int& y, const int randnum)
{
    for(auto& move : moves)
    {
        if(move.first == 0 && move.second == 0) 
        {
            x = move.first;
            y = move.second;
        }
        else if(move.first == 0 && move.second == 7) 
        {
            x = move.first;
            y = move.second;
        }
        else if(move.first == 7 && move.second == 0) 
        {
            x = move.first;
            y = move.second;
        }
        else if(move.first == 7 && move.second == 7) 
        {
            x = move.first;
            y = move.second;
        }
        else if(move.first == 0) 
        {
            x = move.first;
            y = move.second;
        }
        else if(move.first == 7) 
        {
            x = move.first;
            y = move.second;
        }
        else if(move.second == 0) 
        {
            x = move.first;
            y = move.second;
        }
        else if(move.second == 7) 
        {
            x = move.first;
            y = move.second;
        }
        else
        {
            int nMoves = moves.size();
            auto iter = moves.begin();
            for(int i = 0; i < (randnum%nMoves); ++i) ++iter;
            x = iter->first;
            y = iter->second;
        }
    }
}

void playerHuman(const unsigned char** state, const std::set<std::pair<int, int>>& moves, int& x, int& y)
{
    scanf("%d %d", &x, &y);
}

int main()
{
    int wins[2] = {0, 0};
    for(int n = 0; n < 10000; ++n)
    {
    //create board
    OthelloBoard<8, 8> board;

    //initialize random number generator
    std::mt19937 mtRand;
    mtRand.seed(n);
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
                switch(player)
                {
                case 1:
                    //Run player 1 AI
                    playerRandom(board.getState(), board.getValidPlays(), x, y, rand());
                    break;
                case 2:
                    //Run player 2 AI
                    playerCornerEdgeRand(board.getState(), board.getValidPlays(), x, y, rand());
                    break;
                default:
                    //printf("Player not defined!!!\n");
                    break;
                }
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

    wins[winner - 1]++;
    }

    printf("\nWins:\nPlayer X: %d\nPlayer O: %d\n", wins[0], wins[1]); 
}
