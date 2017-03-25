#include "othelloPlayerLOM.h"

#include <cmath>
#include <map>
#include <vector>

OthelloPlayerLOM::OthelloPlayerLOM() {}

void OthelloPlayerLOM::returnPlay(const OthelloBoard<8, 8>& board, int& x, int& y)
{
    std::map<int, std::vector<std::pair<int, int>>> finalMove;

    unsigned char opposingPlayer;
    if(player_ == 1) opposingPlayer = 2;
    else             opposingPlayer = 1;

    for(auto& move : board.getValidPlays())
    {
        //construct hypothetical baord
        OthelloBoard<8, 8> hBoard(board);
        //play current player moves 
        hBoard.play(player_, move.first, move.second);
        //get nMoves for opposing player 
        int nMoves = hBoard.avaliableMoves(opposingPlayer);
        //increase priority of moves in corners 
        if((move.first == 0 || move.first == 7) && (move.second == 0 || move.second == 7))
        {
            nMoves -= 30;
        }
        //Check opponent moves 
        for(auto& opMove : hBoard.getValidPlays())
        {
            //strongly penalize moves that allow opponent to play in a corner
            if((opMove.first == 0 || opMove.first == 7) && (opMove.second == 0 || opMove.second == 7))
            {
                nMoves += 100;
            }

            if((opMove.first >= 1 && opMove.first <= 6) && (opMove.second >= 1 && opMove.second <= 6)) nMoves += 5;
        }
        finalMove[nMoves].push_back(move);
    }
    
    x = finalMove.begin()->second.front().first;
    y = finalMove.begin()->second.front().second;
}
