#include "Game.h"
#include "Rules.h"
#include "stdafx.h"

GameLib::Game::Game(){
    map = GameMap();
    map.Initialize();
    selectedNodeId = -1; 

    mTurnState = PLAYER1PLACE;

    mGameState = PLAYING;

    player1Placed = 0;

    player2Placed = 0;

    player1Alive = 9;

    player1Alive = 9;

}

/*
void GameLib::Game::MousePressed(int pressed){
if (pressed < 0)
{
return;
}
Rules rules = Rules();
switch(mGameState)
{
case PLAYING: 
switch(mTurnState)
{
case PLAYER1PLACE:
{
bool placed = map.PlaceBrick(GameMap::PLAYER1, pressed);
if (placed)
{
Position toPos = map.mapNodes[pressed].position;
bool formedMill = rules.FormedMill(map,toPos);
player1Placed++;
NextTurn(GameMap::PLAYER1, formedMill, &toPos);
}
break;
}
case PLAYER2PLACE:
{
bool placed = map.PlaceBrick(GameMap::PLAYER2, pressed);
if (placed)
{
Position toPos = map.mapNodes[pressed].position;
bool formedMill = rules.FormedMill(map,toPos);
player2Placed++;
NextTurn(GameMap::PLAYER2, formedMill, &toPos);
}
break;
}
case PLAYER1MOVE:
{
PlayerMove(GameMap::PLAYER1,pressed);
break;
}
case PLAYER2MOVE:
{
PlayerMove(GameMap::PLAYER2,pressed);
break;
}
case PLAYER1REMOVE:
{
PlayerRemove(GameMap::PLAYER1,pressed);
break;
}
case PLAYER2REMOVE:
{
PlayerRemove(GameMap::PLAYER2,pressed);
break;
}
}
break;
default:
return;
}

}
*/

void GameLib::Game::CheckGameOver()
{
    Rules rules = Rules();

    Rules::Winner winner = rules.GameOver(map);

    switch(winner)
    {
    case Rules::PLAYER1WIN:
        mGameState = GAMEOVER;
        break;

    case Rules::PLAYER2WIN:
        mGameState = GAMEOVER;
        break;

    case Rules::CONTINIUE:
        return;
        break;

    }
}

bool GameLib::Game::Place( Position aPos, GameMap::Populated player)
{
    Rules rules = Rules();

    int pressed = map.FindNodeId(aPos);

    bool placed = false;

    if(mGameState == PLAYING)
    {
        if((( mTurnState == PLAYER1PLACE && player == GameMap::PLAYER1 )|| ( mTurnState == PLAYER2PLACE && player == GameMap::PLAYER2)) && (pressed != -1))
        {
            placed = map.PlaceBrick(player, pressed);
            if (placed)
            {
                bool formedMill = rules.FormedMill(map,aPos);
                if(player == GameMap::PLAYER1)
                {
                    player1Placed++;
                }
                else
                {
                    player2Placed++;
                }

                NextTurn(player, formedMill, &aPos);
            }
        }
    }

    return placed;
}

bool GameLib::Game::ReMove( Position aPos, GameMap::Populated player)
{
    Rules rules = Rules();

    int pressed = map.FindNodeId(aPos);

    bool removed = false;

    if(mGameState == PLAYING)
    {
        if((( mTurnState == PLAYER1REMOVE && player == GameMap::PLAYER1 )|| ( mTurnState == PLAYER2REMOVE && player == GameMap::PLAYER2)) && (pressed != -1))
        {
            map.Remove(pressed);
            removed = true;

            NextTurn(player, false, &aPos);
        }
    }

    return removed;
}

bool GameLib::Game::Move( Position fromPos, Position toPos, GameMap::Populated player)
{
    Rules rules = Rules();

    bool legal = rules.LegalTurn(mTurnState, map, fromPos, toPos);

    bool moved = false;

    int from = map.FindNodeId(fromPos);

    int to = map.FindNodeId(toPos);
    if(legal && from != -1 && to != -1)
    {

        map.Move(map.mapNodes[from], map.mapNodes[to]);
        bool formedMill = rules.FormedMill(map,toPos);
        NextTurn(player, formedMill, &toPos);
        moved = true;

        //check for game over
        CheckGameOver();
    }


    return moved;
}

std::string GameLib::Game::GetMapDescription()
{
    return map.MapDescription();
}

std::string GameLib::Game::GetTurnDescription()
{
    std::string retString;
    
    if( mTurnState == PLAYER1PLACE ||  mTurnState == PLAYER1MOVE ||  mTurnState == PLAYER1REMOVE)
    {
        retString = "1";
    }
    else
    {
        retString = "2";
    }

    return retString;
}

void GameLib::Game::PlayerMove(GameMap::Populated PLAYER, int pressed)
{
    Rules rules = Rules();
    if(selectedNodeId != -1)
    {
        Position fromPos = map.mapNodes[selectedNodeId].position;
        Position toPos = map.mapNodes[pressed].position;

        bool legal = rules.LegalTurn(mTurnState, map, fromPos, toPos);

        if(legal)
        {
            map.Move(map.mapNodes[selectedNodeId], map.mapNodes[pressed]);
            bool formedMill = rules.FormedMill(map,toPos);
            NextTurn(PLAYER, formedMill, &toPos);

        }
        else
        {
            selectedNodeId = map.SelectNode(PLAYER, pressed);
        }
    }
    else
    {
        selectedNodeId = map.SelectNode(PLAYER, pressed);
    }

    //check for game over
    CheckGameOver();

}

void GameLib::Game::PlayerRemove(GameMap::Populated PLAYER, int pressed)
{
    GameMap::Populated selectedPop = map.mapNodes[pressed].populated;
    if( selectedPop != GameMap::FREE && selectedPop != PLAYER)
    {
        //Remove the selected piece, by setting it to free
        map.Remove(pressed);
        // when removing something, a new mill can't be formed
        NextTurn(PLAYER,false, NULL);
    }
}

GameLib::GameMap::Populated GameLib::Game::GetPlayerTurn()
{
    switch (mTurnState)
    {
    case GameLib::Game::PLAYER1PLACE:
        return GameMap::PLAYER1;
        break;
    case GameLib::Game::PLAYER2PLACE:
        return GameMap::PLAYER2;
        break;
    case GameLib::Game::PLAYER1MOVE:
        return GameMap::PLAYER1;
        break;
    case GameLib::Game::PLAYER2MOVE:
        return GameMap::PLAYER2;
        break;
    case GameLib::Game::PLAYER1REMOVE:
        return GameMap::PLAYER1;
        break;
    case GameLib::Game::PLAYER2REMOVE:
        return GameMap::PLAYER2;
        break;
    default:
        return GameMap::FREE;
        break;
    }
}

char* GameLib::Game::turnText()
{
    switch (mTurnState)
    {
    case Game::PLAYER1PLACE:
        return "Player 1 place";
        break;
    case Game::PLAYER2PLACE:
        return "Player 2 place";
        break;
    case Game::PLAYER1MOVE:
        return "Player 1 move";
        break;
    case Game::PLAYER2MOVE:
        return "Player 2 move";
        break;
    case Game::PLAYER1REMOVE:
        return "Player 1 remove";
        break;
    case Game::PLAYER2REMOVE:
        return "Player 2 remove";
        break;
    default:
        return "";
        break;
    }
}

// change the state of the game to the next, if all bricks has been placed, move into the move phase, ect.
// argument is the current player
void GameLib::Game::NextTurn(GameMap::Populated PLAYER, bool formedMill , Position* toPos)
{
    // reset selected node
    selectedNodeId = -1;
    //TODO: add all the logic states look at wiki for rules
    if(formedMill && toPos != NULL)
    {
        if(PLAYER == GameMap::PLAYER1)
        {
            mTurnState = PLAYER1REMOVE;
        }
        else
        {
            mTurnState = PLAYER2REMOVE;
        }
    }
    else
    {
        if(PLAYER == GameMap::PLAYER1)
        {
            if(player2Placed < 9)
            {
                mTurnState = PLAYER2PLACE;
            }
            else
            {
                mTurnState = PLAYER2MOVE;
            }        
        }
        else
        {
            if(player1Placed < 9)
            {
                mTurnState = PLAYER1PLACE;
            }
            else
            {
                mTurnState = PLAYER1MOVE;
            }
        }
    }

}
