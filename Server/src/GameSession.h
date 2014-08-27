#pragma once
#pragma comment(lib, "GameLib.lib")
//#include "Game.h"
#include "ServerPlayer.h"
#include "Game.h"
#include "Position.h"

/** 
Game session is holds a game session with 2 players connected and the game itself
*/
class GameSession
{
public:

    
    static const int messageSize = 32;
    GameSession(void);
    ~GameSession(void);

    // return true when successfull false when not
    bool Initlialize(ServerPlayer p1, ServerPlayer p2);

    GameLib::Game game;

    ServerPlayer player1, player2;

    void Update(void);
private:

    // Empty is used to be able identify empty or unknown , might need to be split into 2
    // Move is when the cleint want to move, place or remove (a) piece(s)
    // Request is when the client want info about the game, map turn, playernumber
    enum MessageType { EMPTY, MOVE, PLACE, REMOVE, REQUEST};
    enum RequestType { PLAYERINFO, MAPINFO, TURNINFO};
    struct Move
    {
        GameLib::Position pos1; // place remove and move from pos
        GameLib::Position pos2; // move to pos
    };

    // hold info about 
    struct Message
    {
        MessageType type; 
        Move move; // only initalized when type is MOVE
        RequestType request; //only initalized when type is REQUEST

    };

    Message ParseMessage(char *buffer);

    Message ParseMove(std::vector<std::string> splitString);

    Message ParseRequest(std::vector<std::string> splitString);

    Message ErrorMessage(int error);

    void RespondRequest(Message message, ServerPlayer aPlayer);

    // given a message and a player that send it,
    // execute the message and respond to the player
    void ExecAndRespond(GameSession::Message message, ServerPlayer player);

    void ExecAndRespondMove(GameSession::Message message, ServerPlayer player);

    void ExecAndRespondReMove(GameSession::Message message, ServerPlayer player);

    void ExecAndRespondPlace(GameSession::Message message, ServerPlayer player);
    
    void MoveErrorRespond(ServerPlayer aPlayer);

    void UpdatePlayers();
};
