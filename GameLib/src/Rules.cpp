#include "Rules.h"
#include "stdafx.h"
#include "Game.h"

namespace GameLib
{
    //check if a move is legal 
    bool Rules::LegalTurn(Game::TurnState turnState, GameLib::GameMap currentMap, Position fromPosition, Position toPosition)
    {
        switch(turnState)
        {
        case Game::PLAYER1PLACE:
            return true;
            break;  
        case Game::PLAYER2PLACE:
            return true;
            break;

        case Game::PLAYER1MOVE:
            return LegalMove(currentMap,fromPosition,toPosition);
            break;

        case Game::PLAYER2MOVE:
            return LegalMove(currentMap,fromPosition,toPosition);
            break;

        case Game::PLAYER1REMOVE:
            return true;
            break;

        case Game::PLAYER2REMOVE:
            return true;
            break;

        default:
            return true;
        }

    }

    bool Rules::LegalMove(GameMap currentMap, Position fromPosition, Position toPosition)
    {
        GameMap::Node fromNode = currentMap.mapNodes[currentMap.FindNodeId(fromPosition)];
        GameMap::Node toNode = currentMap.mapNodes[currentMap.FindNodeId(toPosition)];

        // the start should not be empty, the end should be empty, and the nodes has tp be connected

        bool emptyStart = fromNode.populated == GameMap::FREE;
        bool emptyEnd = toNode.populated == GameMap::FREE;
        bool differentLocation = !(fromPosition == toPosition);


        return differentLocation && !emptyStart && emptyEnd && (fromNode.rightPosition == toPosition || fromNode.downPosition == toPosition 
            || toNode.downPosition == fromPosition || toNode.rightPosition == fromPosition );
    }

    Rules::Winner GameLib::Rules::GameOver(GameMap curretMap)
    {
        // loop over every node and see if either player 1 or player 2 has less then 3 pieces on the map

        int p1Pieces = 0;
        int p2Pieces = 0;

        for(size_t i = 0; i < curretMap.mapNodes.size(); i++)
        {
            if(curretMap.mapNodes[i].populated == GameMap::PLAYER1)
            {
                p1Pieces++;
            }
            else if(curretMap.mapNodes[i].populated == GameMap::PLAYER2)
            {
                p2Pieces++;
            }
        }

        if(p1Pieces < 3)
        {
            return Rules::PLAYER2WIN;
        }
        else if(p2Pieces  < 3)
        {
            return Rules::PLAYER1WIN;
        }
        else
        {
            return Rules::CONTINIUE;
        }
    }

    // check if a mill has formed by the piece moved to the toPosition
    bool Rules::FormedMill(GameMap currentMap, Position toPosition)
    {
        return FormedMillHorizontal(currentMap, toPosition) || FormedMillVertical(currentMap, toPosition);
    }

    bool Rules::FormedMillHorizontal(GameMap currentMap, Position toPosition)
    {
        GameMap::Node currentNode = currentMap.mapNodes[currentMap.FindNodeId(toPosition)];

        if(currentNode.rightPosition == currentNode.position)
        {
            // the node is all the way to the right in the horizontal line
            GameMap::Node leftNode = currentMap.mapNodes[currentMap.FindNodeIdWhereRight(currentNode.position)];
            GameMap::Node leftLeftNode = currentMap.mapNodes[currentMap.FindNodeIdWhereRight(leftNode.position)];

            return currentNode.populated == leftNode.populated && currentNode.populated == leftLeftNode.populated;
        }
        else
        {
            // the node is in the middle or to the left in the horizontal line
            GameMap::Node rightNode = currentMap.mapNodes[currentMap.FindNodeId(currentNode.rightPosition)];
            if(rightNode.position == rightNode.rightPosition)
            {
                GameMap::Node leftNode = currentMap.mapNodes[currentMap.FindNodeIdWhereRight(currentNode.position)];

                return currentNode.populated == leftNode.populated && currentNode.populated == rightNode.populated;
            }
            else
            {
                GameMap::Node rightRightNode = currentMap.mapNodes[currentMap.FindNodeId(rightNode.rightPosition)];

                return currentNode.populated == rightNode.populated && currentNode.populated == rightRightNode.populated;
            }
        }
    }

    bool Rules::FormedMillVertical(GameMap currentMap, Position toPosition)
    {
        GameMap::Node currentNode = currentMap.mapNodes[currentMap.FindNodeId(toPosition)];

        if(currentNode.downPosition == currentNode.position)
        {
            // the node is all the way to the right in the horizontal line
            GameMap::Node upNode = currentMap.mapNodes[currentMap.FindNodeIdWhereDown(currentNode.position)];
            GameMap::Node upUptNode = currentMap.mapNodes[currentMap.FindNodeIdWhereDown(upNode.position)];

            return currentNode.populated == upNode.populated && currentNode.populated == upUptNode.populated;
        }
        else
        {
            // the node is in the middle or at the top of vertical line
            GameMap::Node downNode = currentMap.mapNodes[currentMap.FindNodeId(currentNode.downPosition)];
            if(downNode.position == downNode.downPosition)
            {
                GameMap::Node upNode = currentMap.mapNodes[currentMap.FindNodeIdWhereDown(currentNode.position)];

                return currentNode.populated == downNode.populated && currentNode.populated == upNode.populated;
            }
            else
            {
                GameMap::Node downDownNode = currentMap.mapNodes[currentMap.FindNodeId(downNode.downPosition)];

                return currentNode.populated == downNode.populated && currentNode.populated == downDownNode.populated;
            }
        }
    }

}