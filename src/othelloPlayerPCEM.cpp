#include "othelloPlayerPCEM.h"

#include <cmath>
#include <map>
#include <vector>

OthelloPlayerPCEM::OthelloPlayerPCEM() {}

void OthelloPlayerPCEM::returnPlay(const OthelloBoard<8, 8>& board, int& x, int& y)
{
    std::map<int, std::vector<std::pair<int, int>>> plays;
    for(auto& move : board.getValidPlays())
    {
        OthelloBoard<8, 8> testboard(board);
        testboard.avaliableMoves(player_);
        testboard.play(player_, move.first, move.second);
        unsigned char opp = (player_ == 1) ? 2 : 1;
        testboard.avaliableMoves(opp);

        //printf("========== OPP BOARD ========== %d, %d\n", move.first, move.second);
        //testboard.print();

        bool skip = false;
        
        auto& oppmoves = testboard.getValidPlays();
        if(oppmoves.empty())
        {
            // if the opponent has no moves, this is a good move (maybe?)
            plays[0].push_back(move);
            break;
        }
        for(auto& tmove : oppmoves)
        {
            if((tmove.first == 0 || tmove.first == 7) && (tmove.second == 0 || tmove.second == 7))
            {
                // this allows the opponent to take a corner, so we avoid it if possible
                plays[3].push_back(move);
                skip = true;
                break;
            }
        }
        if(skip) continue;
        for(auto& tmove : oppmoves)
        {
            //ccheck if the move is within one space of a corner, we want the opponent to play here
            if((tmove.first == 0 && (tmove.second == 1 || tmove.second == 6)) ||
               (tmove.first == 7 && (tmove.second == 1 || tmove.second == 6)) ||
               (tmove.second == 0 && (tmove.first == 1 || tmove.first == 6)) ||
               (tmove.second == 7 && (tmove.first == 1 || tmove.first == 6)))
            {
                plays[0].push_back(move);
                skip = true;
                break;
            }
        }
        if(skip) continue;
        //for(auto& tmove : oppmoves)
        //{
        //    if(tmove.first == 0 || tmove.first == 7 || tmove.second == 0 || tmove.second == 7)
        //    {
        //        // also avoide giving opponent a side if possible, but not as bad as a corner
        //        plays[2].push_back(move);
        //        skip = true;
        //        break;
        //    }
        //}
        //if(skip) continue;
        //if(testboard.count(opp) - board.count(opp) > 3)
        //{
        //    // if the opponent can take too many pieces, avoid this move
        //    plays[2].push_back(move);
        //    continue;
        //}
        plays[1].push_back(move);
    }

    //print all moves in plays
    //for(auto& play : plays)
    //{
    //    printf("Priority %d: ", play.first);
    //    for(auto& move : play.second)
    //    {
    //        printf("(%d, %d) ", move.first, move.second);
    //    }
    //    printf("\n");
    //}

    std::map<int, std::vector<std::pair<int, int>>> plays2;
    for(auto& move : plays.begin()->second)
    {
        if((move.first == 0 || move.first == 7) && (move.second == 0 || move.second == 7))
        {
            plays2[1].push_back(move);
        }
        else if(move.first == 0 || move.first == 7 || move.second == 0 || move.second == 7)
        {
            if(move.first == 1 || move.first == 6 || move.second == 1 || move.second == 6)
            {
                plays2[7 + std::min(int(fabs(3.5 - move.first)), int(fabs(3.5 - move.second)))].push_back(move);
            }
            else
            {
                plays2[2 + std::min(int(fabs(3.5 - move.first)), int(fabs(3.5 - move.second)))].push_back(move);
            }
        }
        else
        {
            plays2[5 + 4*std::max(int(fabs(3.5 - move.first)), int(fabs(3.5 - move.second))) + std::min(int(fabs(3.5 - move.first)), int(fabs(3.5 - move.second)))].push_back(move);
        }
    }

    //print all moves in plays
    //printf("Sorted moves:\n");
    //for(auto& play : plays2)
    //{
    //    printf("Priority %d: ", play.first);
    //    for(auto& move : play.second)
    //    {
    //        printf("(%d, %d) ", move.first, move.second);
    //    }
    //    printf("\n");
    //}

    
    x = plays2.begin()->second.front().first;
    y = plays2.begin()->second.front().second;
}
