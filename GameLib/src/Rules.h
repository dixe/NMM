#ifdef GAMELIB_EXPORTS
#define GAMELIB_API __declspec(dllexport) 
#else
#define GAMELIB_API __declspec(dllimport) 
#endif

#pragma once
#include "GameMap.h"
#include "Game.h"

namespace GameLib
{
    class Rules
    {
    public:

        enum Winner {PLAYER1WIN, PLAYER2WIN, CONTINIUE};

        // check if the turn is legal, no jumping  over other pieces and follow the lines ect.
        bool LegalTurn(Game::TurnState turnState, GameMap currentMap,Position fromPosition, Position toPosition );

        bool FormedMill(GameMap currentMap, Position toPosition);

        // return the winner, or continiue of no winner yet
        Winner GameOver(GameMap curretMap);

    private:
        // checks  if a move is legal, i.e the piece follow line, and there is a piece at fromPos, and not one a toPos
        bool LegalMove(GameMap currentMap, Position fromPosition, Position toPosition );

        bool FormedMillHorizontal(GameMap currentMap, Position toPosition);

        bool FormedMillVertical(GameMap currentMap, Position toPosition);
    };
}