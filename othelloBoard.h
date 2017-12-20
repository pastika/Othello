#include <cstdio>
#include <cstring>
#include <set>
#include <utility>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#ifndef OTHELLOBOARD_h
#define OTHELLOBOARD_h

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/**
 *OthelloBoard holds an othello board of arbitrary size N by M along with the basic play mechanics of the game.
 */
template<const int N, const int M> class OthelloBoard
{
private:
    unsigned char board_[N][M];
    std::set<std::pair<int, int>> moves_;
    unsigned char lastPlayer_;

    inline const bool onBoard(const int x, const int y) const
    {
        return x >= 0 && y >= 0 && x < N && y < M;
    }
    
public:
    /**
     *Constructs an empty othello board ready for play.
     */
    OthelloBoard()
    {
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < M; ++j)
            {
                board_[i][j] = 0;
            }
        }

        board_[N/2 - 1][M/2 -1] = 2;
        board_[N/2    ][M/2 -1] = 1;
        board_[N/2 - 1][M/2   ] = 1;
        board_[N/2    ][M/2   ] = 2;

        lastPlayer_ = 0;
    }

    /**
     *Translates the internal board array into a single non-human readable string which is intended for transmission via network to another client.
     *@return Packaged string containing all the information in the internal board array
     */
    const std::string packageBoard() const 
    {
        std::string boardPackage = std::to_string(N) + " " + std::to_string(M) + " ";
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < M; ++j)
            {
                boardPackage += std::to_string(board_[i][j]);
            }
        }
        //boardPackage += " ; " + std::to_string(moves_.size());
        //for(const auto& move : moves_)
        //{
        //    boardPackage += " - " +  std::to_string(move.first) + " " + std::to_string(move.second);
        //}
        boardPackage += " ; " + std::to_string(lastPlayer_);
        return boardPackage;
    }

    /**
     *Reconstructs an othello board state from a packaged board string
     *@param boardPackage string produced by packageBoard to decode
     *@return returns true if the string is successfully parsed, otherwise false
     */
    bool constructBoard(const std::string boardPackage)
    {
        size_t offset = 0;
        int n = 0, m = 0, nMoves = 0;;
        char buf[N*M + 1];
        int lastPlayer;

        if(!(sscanf(boardPackage.c_str(), "%i %i %s", &n, &m, buf) == 3 && n == N && m == M)) return false;

        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < M; ++j)
            {
                board_[i][j] = static_cast<unsigned char>(buf[i*M + j]) - 48;
            }
        }

        //if((offset = boardPackage.find(";")) == std::string::npos) return false;
        //if(!(sscanf(boardPackage.c_str() + offset + 1, "%i", &nMoves) == 1)) return false;
        //for(int i = 0; i < nMoves; ++i)
        //{
        //    int x = -1;
        //    int y = -1;
        //    if((offset = boardPackage.find("-", offset + 1)) == std::string::npos) return false;
        //    if(!(sscanf(boardPackage.c_str() + offset + 1, "%i %i", &x, &y) == 2 && x >= 0 && y >= 0)) return false;
        //
        //    
        //}

        if((offset = boardPackage.find(";", offset + 1)) == std::string::npos) return false;
        if(!(sscanf(boardPackage.c_str() + offset + 1, "%i", &lastPlayer) == 1)) return false;

        lastPlayer_ = static_cast<unsigned char>(lastPlayer);

        return true;
    }

    /**
     *Determine which player currently is willing the game.   I.e. who has the most pieces of the board.
     *@return returns the player who currently has the most pieces of the baord 
     */
    unsigned char winner() const
    {
        int player[256];
        unsigned char winner = 0;
        int winnerCount = 0;
        for(int i = 0; i < 256; ++i) player[i] = 0;
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < M; ++j)
            {
                ++player[board_[i][j]];
            }
        }
        for(int i = 1; i < 256; ++i)
        {
            if(player[i] > winnerCount)
            {
                winner = i;
                winnerCount = player[i];
            }
        }

        return winner;
    }

    /**
     *Calculates the list of legal moves for the player specified
     *@param player Player to calculate the legal moves for
     *@return The number of legal moves for player 
     */
    int avaliableMoves(const unsigned char player)
    {
        moves_.clear();
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < M; ++j)
            {
                //Skip anf non-blank square
                if(board_[i][j]) continue;

                //check blank squares for possible flips
                const int dirSet[] = {-1, 0, 1};
                for(const int& dirX : dirSet)
                {
                    for(const int& dirY : dirSet)
                    {
                        if(dirX || dirY)
                        {
                            int dir = 1;
                            for(int xp = i + dirX, yp = j + dirY; onBoard(xp, yp) && (!dirX || i != xp) && (!dirY || j != yp); xp += dir*dirX, yp += dir*dirY)
                            {
                                if(board_[xp][yp] == 0) break;
                                if(dir == -1) 
                                {
                                    moves_.insert(std::make_pair(i, j));
                                    break;
                                }
                                if(board_[xp][yp] == player) dir = -1;
                            }
                        }
                    }
                }
            }
        }
        
        return moves_.size();
    }

    /**
     *Place a piece on the board for the specified player.
     *@param player the player who is placing the piece 
     *@param x the x position to place the piece 
     *@param y the y position to place the piece
     *@return If the move was a legal move returns true, otherwise the piece is not placed and the function returns false
     */
    bool play(const unsigned char player, const int x, const int y)
    {
        //Check if play is on board
        if(!onBoard(x, y)) return false;

        //Check if a play was made here 
        if(board_[x][y] != 0) return false;

        //Check if this is a legal move
        if(!moves_.count(std::make_pair(x, y))) return false;

        //Flip spots based on this move
        bool isLegal = false;
        const int dirSet[] = {-1, 0, 1};
        for(const int& dirX : dirSet)
        {
            for(const int& dirY : dirSet)
            {
                if(dirX || dirY)
                {
                    int dir = 1;
                    for(int xp = x + dirX, yp = y + dirY; onBoard(xp, yp) && (!dirX || x != xp) && (!dirY || y != yp); xp += dir*dirX, yp += dir*dirY)
                    {
                        if(board_[xp][yp] == 0) break;
                        if(dir == -1) 
                        {
                            board_[xp][yp] = player; 
                            isLegal = true;
                        }
                        if(board_[xp][yp] == player) dir = -1;
                    }
                }
            }
        }
    
        //Set play if move was legal
        //legal moves are on board, and must flip at least one opponent tile
        if(isLegal) 
        {
            board_[x][y] = player;
            lastPlayer_ = player;
        }
    
        return isLegal;
    }

    /**
     *Print the current board state to the screen.
     */
    void print() const
    {
        std::stringstream ssdstr;
        constructDisplayString(ssdstr);
        printf("%s", ssdstr.str().c_str());
    }

    /**
     *Helper function to construct the current stringstream for the current board state
     *@param ssdstr Stringstream object to fill with the current board state
     */
    void constructDisplayString(std::stringstream& ssdstr) const
    {
        ssdstr << "   ";
        for(int j = 0; j < M; ++j) ssdstr << std::setw(2) << j;
        ssdstr << "\n";
        ssdstr << "   ";
        for(int j = 0; j < 2*M + 1; ++j) ssdstr << "-";
        ssdstr << "\n";

        for(int i = 0; i < N; ++i)
        {
            ssdstr << std::setw(2) << i << " |";
            for(int j = 0; j < M; ++j)
            {
                unsigned char player = 0;
                if(moves_.count(std::make_pair(i, j)))
                {
                    player = 255;
                }
                else
                {
                    player = board_[i][j];
                }
                ssdstr << playerToCharAndColor(player) << "|";
            }
            ssdstr << "\n";
        }

        ssdstr << "   ";
        for(int j = 0; j < 2*M + 1; ++j) ssdstr << "-";
        ssdstr << "\n";
    }

    /**
     *Helper function to convert the current player number into the approperiate display symbol on the screen.
     *@param player The player to return the symbol for
     *@return The symbol corropsonding to player 
     */
    inline char playerToChar(const unsigned char player) const
    {
        switch(player)
        {
        case 0:
            return ' ';
        case 1:
            return 'X';
        case 2:
            return 'O';
        case 255:
            return '+';
        default:
            return '-';
        }
    }

    /**
     *Helper function to convert the current player number into the approperiate display symbol on the screen with color.
     *@param player The player to return the symbol for
     *@return The symbol corropsonding to player 
     */
    inline static const char* playerToCharAndColor(const unsigned char player)
    {
        switch(player)
        {
        case 0:
            return " ";
        case 1:
            return ANSI_COLOR_RED "X" ANSI_COLOR_RESET;
        case 2:
            return ANSI_COLOR_BLUE "O" ANSI_COLOR_RESET;
        case 255:
            return ANSI_COLOR_GREEN "+" ANSI_COLOR_RESET;
        default:
            return "-";
        }
    }

    /**
     *Returns the current state of the OthelloBoard object
     *@return The current state of the OthelloBoard object
     */
    inline const OthelloBoard<8, 8>& getState() const
    {
        return *this;
    }
    
    /**
     *Getter to return the list of valid plays for the current player
     *@return The set of valid plays for the current player
     */
    inline const std::set<std::pair<int, int>>& getValidPlays() const
    {
        return moves_;
    }

    /**
     *The last player to go before the current player
     *@return The last player to go before the current player
     */
    inline const unsigned char getLastPlayer() const
    {
        return lastPlayer_;
    }
};

#endif
