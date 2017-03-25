#include <string>
#include <vector>
#include <utility>

#include <sys/socket.h>

#include "othelloPlayer.h"
#include "othelloPlayerRandom.h"
#include "othelloPlayerCES.h"
#include "othelloPlayerLOM.h"

#ifndef OTHELLOMENU_H
#define OTHELLOMENU_H

class OthelloMenu
{
private:
    int sockd_;
    int verbosity_;

    int gameType_;
    

    enum OTHELLOSTATE
    {
        OS_EXIT, OS_STARTMENU, OS_SETPLAYERSLOT, OS_SETOPPONENT, OS_PLAY
    };
    
    int sendMessage(const std::string mstr)
    {
        int msgLen = mstr.size();
        int byteSent = 0;
        while(msgLen - byteSent)
        {
            if( (byteSent += send(sockd_, mstr.c_str() + byteSent, msgLen, 0)) == -1)
            {
                perror("send");
            }
        }

        return byteSent;
    }

    int recieveResponce()
    {
        const int BUFLEN = 128;
        char buff[BUFLEN];
        int len = 0;
        if( (len = recv(sockd_, buff, BUFLEN - 1, 0)) == -1)
        {
            perror("recv");
        }
        int i = 0;
        for(; i < len; ++i) if(buff[i] == '\r') break;
        buff[i] = '\0';
        if(verbosity_ >= 3) printf("responce: %i %s\n", len, buff);
        if(strcmp("quit", buff) == 0) 
        {
            return -1;
        }
        else if(sscanf(buff, "%i", &i) == 1)
        {
            return i;
        }
        else
        {
            return 0;
        }
    }

    std::pair<std::string, std::vector<int>> openingServerMenu()
    {
        return {"Select game mode:\n\n"
                " 1) Telnet Game \n\n"
                " 2) One Remote Player\n\n"
                " 3) Two Remote Players\n\n",
            {OS_SETPLAYERSLOT} };
    }

    std::pair<std::string, std::vector<int>> selectPlayerSlot()
    {
        return {"Select Your Player Slot:\n\n"
                " 1) Player 1 \n\n"
                " 2) Player 2 \n\n",
            {OS_SETOPPONENT} };
    }

    std::pair<std::string, std::vector<int>> selectOpponentPlayer()
    {
        return {"Select Opponent :\n\n"
                " 1) Random \n\n"
                " 2) CES \n\n"
                " 3) LOM \n\n",
            {OS_PLAY} };
    }

    int arbitrateExchange(int& menu, const std::pair<std::string, std::vector<int>>& textAndSwitch)
    {
        sendMessage(textAndSwitch.first);

        int tmpMenu = recieveResponce();
        printf("tmpMenu: %i\n", tmpMenu);
        if(tmpMenu < 0)        menu = OS_EXIT;
        else if(tmpMenu == 0)  menu = OS_STARTMENU;
        else
        {
            menu = tmpMenu;
            if(menu >= textAndSwitch.second.size()) menu = textAndSwitch.second.size();
            menu = textAndSwitch.second[menu - 1];
        }
        printf("menu: %i\n", menu);
        return tmpMenu;
    }

    bool stateMachineSwitch(int& menu)
    {
        int responce = 0;
        switch(menu)
        {
        case OS_EXIT:
            return false;
        case OS_STARTMENU:
            if(verbosity_ >= 2) printf("Start Menu\n");
            responce = arbitrateExchange(menu, openingServerMenu());
            gameType_ = responce;
            return true;
        case OS_SETPLAYERSLOT:
            if(verbosity_ >= 2) printf("Select Player\n");
            responce = arbitrateExchange(menu, selectPlayerSlot());
            return true;
        case OS_SETOPPONENT:
            if(verbosity_ >= 2) printf("Select Opponent\n");
            responce = arbitrateExchange(menu, selectOpponentPlayer());
            return true;
        case OS_PLAY:
            return false;
        default:
            break;
        }
    }


public:
    OthelloMenu(int sockd)
    {
        sockd_ = sockd;
        gameType_ = 0;
        verbosity_ = -1;
    }

    void setVerbosity(const int verbosity)
    {
        verbosity_ = verbosity;
    }

    int startMenu()
    {
        int menu = 1;
        while(stateMachineSwitch(menu))
        {
        }

        return menu;
    }

};

#endif
