#include "othelloArbiter.h"
#include "othelloPlayerRandom.h"

void playerRandom(const unsigned char** state, const std::set<std::pair<int, int>>& moves, int& x, int& y, const int randnum)
{
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

    OthelloPlayer *p1 = new OthelloPlayerRandom();
    OthelloPlayer *p2 = new OthelloPlayerRandom();

    for(int n = 0; n < 10000; ++n)
    {
        OthelloArbiter oarb;

        oarb.addPlayer(p1);
        oarb.addPlayer(p2);

        unsigned char winner = oarb.playOthello();
        
        wins[winner - 1]++;
    }

    printf("\nWins:\nPlayer X: %d\nPlayer O: %d\n", wins[0], wins[1]); 
}
