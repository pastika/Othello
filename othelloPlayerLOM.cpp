#include "othelloPlayerLOM.h"

#include <cmath>
#include <map>
#include <vector>

OthelloPlayerLOM::OthelloPlayerLOM() {}

void OthelloPlayerLOM::returnPlay(const OthelloBoard<8, 8>& board, int& x, int& y)
{
    std::map<int, std::vector<std::pair<int, int>>> finalMove;

    unsigned char lastPlayer = board.getLastPlayer();
    unsigned char player;
    if(lastPlayer == 1) player = 2;
    else                player = 1;

    for(auto& move : board.getValidPlays())
    {
        OthelloBoard<8, 8> hBoard(board);
        hBoard.play(player, move.first, move.second);
        int nMoves = hBoard.avaliableMoves(lastPlayer);
        if((move.first == 0 || move.first == 7) && (move.second == 0 || move.second == 7))
        {
            nMoves -= 20;
        }
        for(auto& opMove : hBoard.getValidPlays())
        {
            if((opMove.first == 0 || opMove.first == 7) && (opMove.second == 0 || opMove.second == 7))
            {
                nMoves += 100;
            }
            else if(opMove.first == 0 || opMove.first == 7 || opMove.second == 0 || opMove.second == 7)
            {
                nMoves += 10;
            }
        }
        finalMove[nMoves].push_back(move);
    }
    
    x = finalMove.begin()->second.front().first;
    y = finalMove.begin()->second.front().second;
}

int OthelloPlayerLOM::sum(const int i, int sum, const OthelloBoard<8, 8>& board)
{
    auto& moves = board.getValidPlays();
    OthelloBoard<8, 8> hBoard(board);
}
