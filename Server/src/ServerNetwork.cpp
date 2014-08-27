// Server.cpp : Defines the entry point for the console application.
//

#include "ServerNetwork.h"
#include <ws2tcpip.h>

ServerNetwork::ServerNetwork(void)
{
    // create WSADATA object
    WSADATA wsaData;

    // initialize the socket to invalid

    clientSocket = INVALID_SOCKET;
    listenSocket = INVALID_SOCKET;

    struct  addrinfo *result = NULL;
    struct  addrinfo hints;


    // initialize windsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if( iResult != 0)
    {
        printf("WSAStartup failed with error %d/n",iResult);
        exit(1);
    }

    // setup the address information
    // fill hints with 0's
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;


    // resolve server address and port
    iResult = getaddrinfo(NULL,DEFAULT_PORT,&hints, & result);
    if( iResult != 0)
    {
        printf("getaddrinfo failed with error %d/n", iResult);
        exit(1);
    }

    listenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if(listenSocket == INVALID_SOCKET)
    {
        printf("listen socket fialed with error %d/n", WSAGetLastError());   
        freeaddrinfo(result);
        WSACleanup();
        exit(1);

    }

    // set listen socket to be nonblocking
    u_long iMode = 1;
    iResult = ioctlsocket(listenSocket,FIONBIO, &iMode);

    if (iResult == SOCKET_ERROR) {
        printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        exit(1);
    }

    iResult = bind(listenSocket, result->ai_addr, (int) result->ai_addrlen);

    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        exit(1);
    }

    freeaddrinfo(result);

    iResult = listen(listenSocket,SOMAXCONN);

    if (iResult == SOCKET_ERROR) {
        printf("listen failed failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        exit(1);
    }
}

bool ServerNetwork::AcceptNewClient(unsigned int &id)
{
    // if client is waiting, accept the connection and sace the socket
    clientSocket = accept(listenSocket, NULL, NULL);

    if( clientSocket != INVALID_SOCKET)
    {
        // disable nagle on the client socket
        char value = 1;
        setsockopt(clientSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));

        // insert the new client in the session id table
        sessions.insert(std::pair<unsigned int, SOCKET>(id, clientSocket));

        return true;
    }
    return false;
}

// return found socket if the key value exist in the map, else return a socket set to invalid
SOCKET ServerNetwork::GetClientSocket(unsigned int &id)
{
    // get the iterator the the player sessu

    if(sessions.count(id) > 0)
    {
    std::map<unsigned int, SOCKET>::iterator iter = sessions.find(id);
    return iter->second;
    }
    else
    {
        SOCKET s = INVALID_SOCKET;
        return s;
    }
}

ServerNetwork::~ServerNetwork(void)
{
    // TODO release every thing
}

