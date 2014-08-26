
#include "ServerNetwork.h"
#include "ServerPlayer.h"
#include "GameSession.h"

int main(int argc, char* argv[])
{
    // setup network to accept and save incomming connections
    ServerNetwork network = ServerNetwork();
    // two players 
    ServerPlayer player1;
    ServerPlayer player2;
    GameSession gameSes;
    // to print or not
    bool p=false;
    bool createdGS = false;
    unsigned int clientid = 1;
    while(1)
    {
        // when a new connections is made, it gets saved in network.sessions, with key clientid
        if( network.AcceptNewClient(clientid))
        {
            // setup the two players 
            printf("client %d connection\n", clientid);
            if(clientid == 1){
                player1.Initialize(network.GetClientSocket(clientid), GameLib::GameMap::PLAYER1);

            }
            if(clientid == 2){
                player2.Initialize(network.GetClientSocket(clientid),GameLib::GameMap::PLAYER2);
                // create a game session with player1 and player2

                gameSes = GameSession();
                gameSes.Initlialize(player1,player2);
                p = true;
            }
            clientid++;
        }

        if(p)
        {
            // read input from bother player, if no new input, buffer keeps at ""
            gameSes.Update();

        }

    }

    return 0;
}
