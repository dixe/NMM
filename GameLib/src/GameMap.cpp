#include "stdafx.h"
#include "GameMap.h"
#include "Position.h"

namespace GameLib
{
void GameMap::Initialize(){
    SetupNineMMMap();
}

// assume checks has been made to validate if the move is legal according to the rules before calling this function
void GameMap::Move(Node &fromNode, Node &toNode)
{
    // the move can be made
    toNode.populated = fromNode.populated;
    fromNode.populated = FREE;

}

//Sets selected node population to free
void GameMap::Remove(int selectedNode)
{
    mapNodes[selectedNode].populated = FREE;
}

bool GameMap::PlaceBrick(Populated PLAYER, int nodeId)
{
    if(mapNodes[nodeId].populated == FREE)
    {
        mapNodes[nodeId].populated = PLAYER;
        return true;
    }

    return false;
}

int GameMap::SelectNode(Populated PLAYER, int nodeId)
{
    if(mapNodes[nodeId].populated == PLAYER)
    {
        return nodeId;
    }
    return -1;
}

int GameMap::FindNodeId(Position position)
{
    for( int i = 0; i < (int) mapNodes.size(); i++)
    {
        Node node = mapNodes[i];
        if(node.position == position)
        {
            return node.nodeId;
        }
    }

    return -1;
}

// given a position, return the node id where tis position is the down, if not found returns -1
int GameMap::FindNodeIdWhereDown(Position downPosition)
{
    for( int i = 0; i < (int) mapNodes.size(); i++)
    {
        Node node = mapNodes[i];
        if(node.downPosition == downPosition && node.position != downPosition)
        {
            return node.nodeId;
        }
    }

    return -1;

}

// given a position, return the node id where this position is the right, if not found returns -1
int GameMap::FindNodeIdWhereRight(Position rightPosition)
{
    for( int i = 0; i < (int) mapNodes.size(); i++)
    {
        Node node = mapNodes[i];
        if(node.rightPosition == rightPosition && node.position != rightPosition)
        {
            return node.nodeId;
        }
    }

    return -1;

}

void GameMap::SetupNineMMMap()
{
    //  setup the nine mens morris map

    for(int i = 0; i < 24; i++)
    {
        Node node = Node();
        node.nodeId = i;
        node.populated = FREE;

        switch(i)
        {
        case 0:
            node.position.letter = Position::A;
            node.position.number = Position::ONE;

            node.downPosition = node.position;

            node.rightPosition.letter = Position::D;
            node.rightPosition.number = Position::ONE;

            mapNodes.push_back(node);

            break;
        case 1:
            node.position.letter = Position::D;
            node.position.number = Position::ONE;

            node.downPosition = node.position;

            node.rightPosition.letter = Position::G;
            node.rightPosition.number = Position::ONE;


            mapNodes.push_back(node);

            break;
        case 2:
            node.position.letter = Position::G;
            node.position.number = Position::ONE;

            node.downPosition = node.position;
            node.rightPosition = node.position;

            mapNodes.push_back(node);

            break;

        case 3:
            node.position.letter = Position::B;
            node.position.number = Position::TWO;

            node.downPosition.letter = Position::B;
            node.downPosition.number = Position::TWO;

            node.rightPosition.letter = Position::D;
            node.rightPosition.number = Position::TWO;


            mapNodes.push_back(node);

            break;
        case 4:
            node.position.letter = Position::D;
            node.position.number = Position::TWO;

            node.downPosition.letter = Position::D;
            node.downPosition.number = Position::ONE;

            node.rightPosition.letter = Position::F;
            node.rightPosition.number = Position::TWO;

            mapNodes.push_back(node);

            break;
        case 5:
            node.position.letter = Position::F;
            node.position.number = Position::TWO;

            node.downPosition.letter = Position::F;
            node.downPosition.number = Position::TWO;

            node.rightPosition.letter = Position::F;
            node.rightPosition.number = Position::TWO;

            mapNodes.push_back(node);

            break;
        case 6:
            node.position.letter = Position::C;
            node.position.number = Position::THREE;

            node.downPosition.letter = Position::C;
            node.downPosition.number = Position::THREE;

            node.rightPosition.letter = Position::D;
            node.rightPosition.number = Position::THREE;

            mapNodes.push_back(node);
            break;
        case 7:
            node.position.letter = Position::D;
            node.position.number = Position::THREE;

            node.downPosition.letter = Position::D;
            node.downPosition.number = Position::TWO;

            node.rightPosition.letter = Position::E;
            node.rightPosition.number = Position::THREE;

            mapNodes.push_back(node);
            break;
        case 8:
            node.position.letter = Position::E;
            node.position.number = Position::THREE;

            node.downPosition.letter = Position::E;
            node.downPosition.number = Position::THREE;

            node.rightPosition.letter = Position::E;
            node.rightPosition.number = Position::THREE;

            mapNodes.push_back(node);
            break;
        case 9:
            node.position.letter = Position::A;
            node.position.number = Position::FOUR;

            node.downPosition.letter = Position::A;
            node.downPosition.number = Position::ONE;

            node.rightPosition.letter = Position::B;
            node.rightPosition.number = Position::FOUR;

            mapNodes.push_back(node);
            break;
        case 10:
            node.position.letter = Position::B;
            node.position.number = Position::FOUR;

            node.downPosition.letter = Position::B;
            node.downPosition.number = Position::TWO;

            node.rightPosition.letter = Position::C;
            node.rightPosition.number = Position::FOUR;

            mapNodes.push_back(node);
            break;
        case 11:
            node.position.letter = Position::C;
            node.position.number = Position::FOUR;

            node.downPosition.letter = Position::C;
            node.downPosition.number = Position::THREE;

            node.rightPosition.letter = Position::C;
            node.rightPosition.number = Position::FOUR;

            mapNodes.push_back(node);
            break;
        case 12:
            node.position.letter = Position::E;
            node.position.number = Position::FOUR;

            node.downPosition.letter = Position::E;
            node.downPosition.number = Position::THREE;

            node.rightPosition.letter = Position::F;
            node.rightPosition.number = Position::FOUR;

            mapNodes.push_back(node);
            break;
        case 13:
            node.position.letter = Position::F;
            node.position.number = Position::FOUR;

            node.downPosition.letter = Position::F;
            node.downPosition.number = Position::TWO;

            node.rightPosition.letter = Position::G;
            node.rightPosition.number = Position::FOUR;

            mapNodes.push_back(node);
            break;
        case 14:
            node.position.letter = Position::G;
            node.position.number = Position::FOUR;

            node.downPosition.letter = Position::G;
            node.downPosition.number = Position::ONE;

            node.rightPosition.letter = Position::G;
            node.rightPosition.number = Position::FOUR;

            mapNodes.push_back(node);
            break;
        case 15:
            node.position.letter = Position::C;
            node.position.number = Position::FIVE;

            node.downPosition.letter = Position::C;
            node.downPosition.number = Position::FOUR;

            node.rightPosition.letter = Position::D;
            node.rightPosition.number = Position::FIVE;

            mapNodes.push_back(node);
            break;
        case 16:
            node.position.letter = Position::D;
            node.position.number = Position::FIVE;

            node.downPosition.letter = Position::D;
            node.downPosition.number = Position::FIVE;

            node.rightPosition.letter = Position::E;
            node.rightPosition.number = Position::FIVE;

            mapNodes.push_back(node);
            break;
        case 17:
            node.position.letter = Position::E;
            node.position.number = Position::FIVE;

            node.downPosition.letter = Position::E;
            node.downPosition.number = Position::FOUR;

            node.rightPosition.letter = Position::E;
            node.rightPosition.number = Position::FIVE;

            mapNodes.push_back(node);
            break;
        case 18:
            node.position.letter = Position::B;
            node.position.number = Position::SIX;

            node.downPosition.letter = Position::B;
            node.downPosition.number = Position::FOUR;

            node.rightPosition.letter = Position::D;
            node.rightPosition.number = Position::SIX;

            mapNodes.push_back(node);
            break;
        case 19:
            node.position.letter = Position::D;
            node.position.number = Position::SIX;

            node.downPosition.letter = Position::D;
            node.downPosition.number = Position::FIVE;

            node.rightPosition.letter = Position::F;
            node.rightPosition.number = Position::SIX;

            mapNodes.push_back(node);
            break;
        case 20:
            node.position.letter = Position::F;
            node.position.number = Position::SIX;

            node.downPosition.letter = Position::F;
            node.downPosition.number = Position::FOUR;

            node.rightPosition.letter = Position::F;
            node.rightPosition.number = Position::SIX;

            mapNodes.push_back(node);
            break;
        case 21:
            node.position.letter = Position::A;
            node.position.number = Position::SEVEN;

            node.downPosition.letter = Position::A;
            node.downPosition.number = Position::FOUR;

            node.rightPosition.letter = Position::D;
            node.rightPosition.number = Position::SEVEN;

            mapNodes.push_back(node);
            break;
        case 22:
            node.position.letter = Position::D;
            node.position.number = Position::SEVEN;

            node.downPosition.letter = Position::D;
            node.downPosition.number = Position::SIX;

            node.rightPosition.letter = Position::G;
            node.rightPosition.number = Position::SEVEN;

            mapNodes.push_back(node);
            break;
        case 23:
            node.position.letter = Position::G;
            node.position.number = Position::SEVEN;

            node.downPosition.letter = Position::G;
            node.downPosition.number = Position::FOUR;

            node.rightPosition.letter = Position::G;
            node.rightPosition.number = Position::SEVEN;

            mapNodes.push_back(node);
            break;

        }
    }
}

}