#pragma once
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#include <WinSock2.h>
#include <map>
#include "ServerPlayer.h"

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "6881" 

class ServerNetwork
{
public:
    ServerNetwork(void);
    ~ServerNetwork(void);
    
    SOCKET listenSocket;

    SOCKET clientSocket;

    std::map<unsigned int,SOCKET> sessions;    
  
    int iResult;

    bool AcceptNewClient(unsigned int &id);

    SOCKET GetClientSocket(unsigned int &id);

};

