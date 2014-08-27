#ifdef GAMELIB_EXPORTS
#define GAMELIB_API __declspec(dllexport) 
#else
#define GAMELIB_API __declspec(dllimport) 
#endif
#pragma once

#include "Util.h"
#include "GameMap.h"

namespace GameLib
{
    // the game itself
    class Game
    {
    public:
        enum TurnState {PLAYER1PLACE, PLAYER2PLACE, PLAYER1MOVE, PLAYER2MOVE, PLAYER1REMOVE, PLAYER2REMOVE };

        enum  GameState {PAUSE, PLAYING, GAMEOVER };

        GameMap map;

        GAMELIB_API Game();

        //try to place a piece belonging to player on the position, return true if sussecfill successfull, false if not
        GAMELIB_API bool Place( Position aPos, GameMap::Populated player);

        GAMELIB_API bool ReMove( Position aPos, GameMap::Populated player);
        
        // like playerMove, but useable with 2 pos and a player, to be used by the server
        GAMELIB_API bool Move( Position fromPos, Position toPos, GameMap::Populated player);

        int selectedNodeId;

        char* turnText();

        GAMELIB_API GameMap::Populated GetPlayerTurn();
        
        GAMELIB_API std::string GetMapDescription();

        GAMELIB_API std::string GetTurnDescription();

    private:

        int player1Placed;

        int player2Placed; 

        int player1Alive;

        int player2Alive;

        TurnState mTurnState;

        GameState mGameState;

        void PlayerMove(GameMap::Populated PLAYER, int pressed);

        void PlayerRemove(GameMap::Populated PLAYER, int pressed);

        void NextTurn(GameMap::Populated PLAYER, bool formedmil, Position* toPos);

        void CheckGameOver();
    };
}
