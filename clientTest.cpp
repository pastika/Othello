/*
** client.c -- a stream socket client demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#include "othelloBoard.h"

#define PORT "3490" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) 
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    int sockfd, numbytes;  
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    if (argc != 2) 
    {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) 
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) 
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
        {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
        {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) 
    {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) 
    {
        perror("recv");
        exit(1);
    }

    if ((numbytes = send(sockfd, "quit", 4, 0)) == -1) 
    {
        perror("send");
        exit(1);
    }

    while(1)
    {
        //waiting for message from server
        //message format
        // message ; current player ; board package ; last player
        if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) 
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
            printf("Player %s Choose move.\n", board.playerToCharAndColor(player));
            fflush(stdin);
        }
        while(scanf("%i %i", &x, &y) != 2); //cycle until a valid move is provided

        //Parse move and send back to server 
        sprintf(buf, "%i %i", x ,y);
        if ((numbytes = send(sockfd, buf, strlen(buf), 0)) == -1) 
        {
            perror("send");
            exit(1);
        }
    }

    close(sockfd);

    return 0;
}
