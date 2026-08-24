#include <set>
#include <utility>

#include "othelloBoard.h"

#ifndef OTHELLOPLAYER_h
#define OTHELLOPLAYER_h

/**
 *Base class to define an othello player.  
 */
class OthelloPlayer
{
private:
    /**
     *Internal function to calculate the players next play based upon the othello board.
     *This function must be overridden by the child player class.  
     *@param board The current state of the OthelloBoard
     *@param x The x position of the play returned 
     *@param y The y position of the play returned
     */
    virtual void returnPlay(const OthelloBoard<8, 8>&, int&, int&) = 0;

protected:
    ///Internal variable to track which player this in the game
    unsigned char player_;

public:
    /**
     *External interface to the returnPlay function.
     */
    inline void operator()(const OthelloBoard<8, 8>& board, int& x, int& y)
    {
        returnPlay(board, x, y);
    }

    /**
     *Set which player position in the game this OthelloPlayer will be (1 or 2 for a traditional game)
     *@param The assigned player position
     */
    void setPlayer(const unsigned char player)
    {
        player_ = player;
    }

    /**
     *This function is used to inform the OthelloPlayer which of the players won the game and provide the final board state.
     *It is optional to redefine this method.  The player may choose to ignore this information, in which case the default definition is sufficient. 
     *@param winner The player position of the winning player
     *@param The board state at the end of the game
     */
    virtual void winner(const unsigned char winner, const OthelloBoard<8, 8>& board)
    {
    }
};

#endif
