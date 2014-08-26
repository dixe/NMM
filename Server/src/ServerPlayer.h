#pragma once
/*
Server player hold info of one player on the server
*/
#include <WinSock2.h>
#include "GameMap.h"

class ServerPlayer
{
public:
    ServerPlayer(void);
    ~ServerPlayer(void);

    bool Initialize(SOCKET aPlayerSocket, GameLib::GameMap::Populated player);
    void Receive(char* buffer, int len);
    void ServerPlayer::Send(char* buffer, int len);
    bool isInitialized();

    GameLib::GameMap::Populated GetPlayer();

private:
    
    GameLib::GameMap::Populated player;

    bool initialized;
    SOCKET playerSocket;
};

