#include "ServerPlayer.h"

ServerPlayer::ServerPlayer()
{
}

GameLib::GameMap::Populated ServerPlayer::GetPlayer()
{
    return player;
}



bool ServerPlayer::Initialize(SOCKET aPlayerSocket, GameLib::GameMap::Populated aplayer)
{
    if(aPlayerSocket != INVALID_SOCKET)
    {
        // set the player socket to the argument
        playerSocket = aPlayerSocket;

        // set the player socket to be non-blocking 
        u_long iMode=1;
        int res = ioctlsocket(playerSocket, FIONBIO, &iMode);

        if( res == 0)
        {
            initialized = true;
            player = aplayer;
        }
    }
    return initialized;
}

ServerPlayer::~ServerPlayer(void)
{
    // todo cleanup the socket
}

void ServerPlayer::Receive(char* buffer, int len)
{
    recv(playerSocket, buffer,len,0);
}

void ServerPlayer::Send(const char* buffer, int len)
{
    send(playerSocket,buffer,len,0);
}

bool ServerPlayer::isInitialized()
{
    return initialized;
}