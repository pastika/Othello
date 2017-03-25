#include "othelloArbiterClient.h"

OthelloArbiterClient::OthelloArbiterClient(int sockd)
{
    sockd_ = sockd;
    verbosity_ = -1;
}

void OthelloArbiterClient::setPlayer(OthelloPlayer* player)
{
    player_.reset(player);
}

void OthelloArbiterClient::setVerbosity(int verbosity)
{
    verbosity_ = verbosity;
}

void OthelloArbiterClient::beginArbitration()
{
    int numbytes;
    const int MAXDATASIZE = 256;
    char buf[MAXDATASIZE];

    while(1)
    {
        //waiting for message from server
        //message format
        // message ; current player ; board package ; last player
        if ((numbytes = recv(sockd_, buf, MAXDATASIZE-1, 0)) == -1) 
        {
            perror("recv");
            exit(1);
        }

        //ensure zero termination of string
        buf[numbytes] = '\0';

        //partition initial message from game data
        char * startPos = strstr(buf, ";");
        *startPos = '\0';

        //parse initial message 
        bool stop = false;
        if(strstr(buf, "winner"))
        {
            //What to do if the game is over and a winner is declared 
            unsigned char winner;
            sscanf(buf, "winner: %hhu", &winner);
            printf("Winner %s\n", OthelloBoard<8,8>::playerToCharAndColor(winner));
            stop = true; // stop after one last display of the game baord 
        }
        else if(strstr(buf, "play"))
        {
            //what to do if the request to play is sent
            //DO NOTIHNG
        }
        else
        {
            //Display any other message than "play" and continue to play as usual
            printf("%s\n", buf);
        }
        ++startPos;

        //extract the current player from the game state data
        unsigned char player;
        if( sscanf(startPos, "%hhu", &player) != 1)
        {
            printf("Player parse failure\n");
        }

        //advance to board data
        startPos = strstr(startPos, ";") + 1;

        //reconstruct the board from the given data
        OthelloBoard<8, 8> board;
        board.constructBoard(startPos);
        //compute the avaliable moves
        board.avaliableMoves( player );
        //display the board
        printf("\n");
        board.print();
        printf("\n");

        //Stop if a winner has been declared 
        if(stop) break;

        //If this is a normal turn prompt the player for a move
        int x, y;
        do
        {
            if(verbosity_ >= 1) printf("Player %s Choose move.\n", board.playerToCharAndColor(player));
            do
            {
                (*player_)(board.getState(), x, y);
            }
            while(board.getValidPlays().count(std::make_pair(x, y)) == 0);
        }
        while(!board.play(player, x, y));
        
        if(verbosity_ >= 1) printf("Input: %d %d\n", x, y);

        //Parse move and send back to server 
        sprintf(buf, "%i %i", x ,y);
        if ((numbytes = send(sockd_, buf, strlen(buf), 0)) == -1) 
        {
            perror("send");
            exit(1);
        }
    }

}
