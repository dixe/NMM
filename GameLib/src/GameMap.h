#ifdef GAMELIB_EXPORTS
#define GAMELIB_API __declspec(dllexport) 
#else
#define GAMELIB_API __declspec(dllimport) 
#endif

#pragma once

#include <vector>
#include <Windows.h>
#include "Position.h"

namespace GameLib
{
    class GameMap
    {
    public:
        GAMELIB_API enum Populated { FREE, PLAYER1, PLAYER2 };

        struct Node
        {
            int nodeId;// every node has a unique id, from 0 to 23
            Populated populated; // whether its free, have player or player 2 unit on it
            //TODO: might want to store the acutal piece here, and not just true/false;
            Position position; // position of the node on the map
            // right and down, will be set to self, if not used
            Position rightPosition; // the node that is to the right
            Position downPosition; // node that is down
        };

        std::string MapDescription();

        // node id, correspond to index into mapNodes vector
        std::vector<Node> mapNodes;

        void Initialize();

        // assume checks has been made to validate if the move is legal according to the rules before calling this function
        void Move(Node &fromNode, Node &toNode);

        //Sets selected node population to free
        void Remove(int selectedNode);

        // try to place the a brick, return true if place, false if not
        bool PlaceBrick(Populated PLAYER, int nodeId);

        // return the node id if the node id can be pressed, return -1 if its not a legal selection for the player
        int SelectNode(Populated PLAYER, int nodeId);

        // given a position, return the node id, if not found returns -1
        int FindNodeId(Position position);

        // given a position, return the node id where tis position is the down, if not found returns -1
        int FindNodeIdWhereDown(Position downPosition);

        // given a position, return the node id where this position is the right, if not found returns -1
        int FindNodeIdWhereRight(Position rightPosition);


    private:
        void SetupNineMMMap();
    };
}