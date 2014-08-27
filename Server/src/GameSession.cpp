#include "GameSession.h"
#include <string>
#include "StringUtil.h"

GameSession::GameSession(void)
{

}


GameSession::~GameSession(void)
{
}

// return true when successfull false when not
bool GameSession::Initlialize(ServerPlayer p1, ServerPlayer p2)
{
    if(p1.isInitialized() && p2.isInitialized())
    {
        // setup the players
        player1 = p1;
        player2 = p2;

        // setup the game
        game = GameLib::Game();

        return true;
    }
    return false;

}

void GameSession::Update(void)
{
    // listen to both players
    char p1buffer[messageSize] = ""; 
    char p2buffer[messageSize] = "";

    // parse player 1 message and repsond
    player1.Receive(p1buffer, messageSize);

    Message p1Message = ParseMessage(p1buffer);

    ExecAndRespond(p1Message, player1);

    // parse player 2 message and repsond
    player2.Receive(p2buffer, messageSize);
    Message p2Message = ParseMessage(p2buffer);

    ExecAndRespond(p2Message, player2);

    // update players with turn info
    UpdatePlayers();

}

GameSession::Message GameSession::ParseMessage(char *buffer)
{
    using namespace std;
    string newBuffer = buffer;
    Strip(newBuffer);
    vector<string> words = Split(newBuffer," ");
    // read the first char in buffer
    if(words.size() >= 1)
    {
        switch(words[0][0])
        {
        case '1': // client move
            return ParseMove(words);
            break;
        case '2':
            return ParseRequest(words);
            break;
        default:
            return ErrorMessage(0);
            break;
        }

    }
    else
    {
        //TODO Error, message can't be shorter then 3 chars
        return ErrorMessage(0);
    }
    // pased on buffer content contruct the message

    // return the message

}

GameSession::Message GameSession::ParseMove(std::vector<std::string> words)
{
    // words[0] is 1xy 
    // words[0][2] is the y 
    switch(words[0][2])
    {
    case '1': // move, the buffer len should be over 9 chars
        {
            if(words.size() < 3 || words[1].length() < 2 || words[2].length() < 2)
            {
                return ErrorMessage(0);
            }
            if(words[1][0] <'A' || words[1][0]> 'F' || words[2][0] < 'A' || words[2][0] > 'F')
            {
                return ErrorMessage(0);
            }
            if(words[1][1] <'1' || words[1][1] > '9' || words[2][1] < '1' || words[2][1] > '9')
            {
                return ErrorMessage(0);
            }

            Move move = Move();
            char letter = words[1][0];
            int num = words[1][1] - '0';
            move.pos1 = GameLib::CreatePos(letter, num - 1);

            letter = words[2][0];
            num = words[2][1] - '0';
            move.pos2 = GameLib::CreatePos(letter, num - 1);

            // create the move message
            Message retmes = Message();
            retmes.type = MOVE;
            retmes.move = move;
            return retmes;

            break;
        }
    case '2':
        {
            if(words.size() < 2 || words[1].length() < 2)
            {
                return ErrorMessage(0);
            }
            if(words[1][0] <'A' || words[1][0]> 'F' )
            {
                return ErrorMessage(0);
            }
            if(words[1][1] <'1' || words[1][1] > '9')
            {
                return ErrorMessage(0);
            }
            Move move = Move();

            char letter = words[1][0];
            int num = words[1][1] - '0';
            move.pos1 = GameLib::CreatePos(letter, num - 1);

            // create the move message
            Message retmes = Message();
            retmes.type = PLACE;
            retmes.move = move;
            return retmes;
            break;
        }
        break;
    case '3':
        {
            if(words.size() < 2 || words[1].length() < 2)
            {
                return ErrorMessage(0);
            }
            if(words[1][0] <'A' || words[1][0]> 'F' )
            {
                return ErrorMessage(0);
            }
            if(words[1][1] <'1' || words[1][1] > '9')
            {
                return ErrorMessage(0);
            }
            Move move = Move();
            char letter = words[1][0];
            int num = words[1][1] - '0';

            move.pos1 = GameLib::CreatePos(letter, num - 1);            
            // create the move message
            Message retmes = Message();
            retmes.type = REMOVE;
            retmes.move = move;
            return retmes;
            break;
        }
        break;
    }

    return ErrorMessage(0);
}

GameSession::Message GameSession::ParseRequest(std::vector<std::string> words)
{

    // create the move message
    Message retmes = Message();
    retmes.type = REQUEST;
    switch (words[0][2])
    {
    case '1':
        retmes.request = PLAYERINFO;
        break;
    case '2':
        retmes.request = MAPINFO;
        break;
    case '3':
        retmes.request = TURNINFO;
        break;
    default:
        return ErrorMessage(0);
        break;
    }
    return retmes;
}

GameSession::Message GameSession::ErrorMessage(int error)
{
    // TODO use int error to expand error message types
    Message retmes = Message();
    retmes.type = EMPTY;
    return retmes;
}

void GameSession::RespondRequest(Message message, ServerPlayer aPlayer)
{
    char buffer[16];
    switch (message.request)
    {
    case  PLAYERINFO:
        {
            std::string infostring = "501 ";
            char playerNum = (int)aPlayer.GetPlayer() + '1';
            infostring.append(sizeof(playerNum),playerNum);
            aPlayer.Send(infostring.c_str(),infostring.length());
            break;
        }
    case MAPINFO:
        {
            std::string infostring = "502 ";
            infostring.append(game.GetMapDescription());
            aPlayer.Send(infostring.c_str(),infostring.length());
            break;
        }
    case TURNINFO:
        {
            std::string infostring = "503 ";
            infostring.append(game.GetTurnDescription());
            aPlayer.Send(infostring.c_str(),infostring.length());
            break;
        }
    default:
        break;
    }
}

void GameSession::ExecAndRespond(Message message, ServerPlayer player)
{
    switch (message.type)
    {
    case MOVE:
        ExecAndRespondMove(message,player);
        break;

    case REMOVE:
        ExecAndRespondReMove(message,player);
        break;

    case PLACE:
        ExecAndRespondPlace(message,player);
        break;
    case REQUEST:
        RespondRequest(message, player);
        break;
    default:
        break;
    }
}

void GameSession::ExecAndRespondMove(Message message, ServerPlayer aPlayer)
{
    if(game.Move(message.move.pos1, message.move.pos2, aPlayer.GetPlayer()))
    {
        char* buffer = "301";
        aPlayer.Send(buffer,3);

        char desbuf[15];
        char letter = (char) (message.move.pos1.letter + 'A');
        char num = message.move.pos1.number + '1';

        char letter2 = (char) (message.move.pos2.letter + 'A');
        char num2 = message.move.pos2.number + '1';

        sprintf_s(desbuf,"401 %d %c%c %c%c", aPlayer.GetPlayer(), letter, num, letter2, num2);

        // send the new move to every player
        player1.Send(desbuf,strlen(desbuf));
        player2.Send(desbuf,strlen(desbuf));
    }
    else
    {
        MoveErrorRespond(aPlayer);
    }
}

void GameSession::ExecAndRespondPlace(Message message, ServerPlayer aPlayer)
{
    if(game.Place(message.move.pos1, aPlayer.GetPlayer()))
    {
        char* buffer = "301";
        aPlayer.Send(buffer,3);

        char desbuf[12];
        char letter = (char) (message.move.pos1.letter + 'A');
        char num = message.move.pos1.number + '1';

        sprintf_s(desbuf,"402 %d %c%c",aPlayer.GetPlayer(), letter,num);

        // send the new move to every player
        player1.Send(desbuf,strlen(desbuf));
        player2.Send(desbuf,strlen(desbuf));
    }
    else
    {
        MoveErrorRespond(aPlayer);
    }
}

void GameSession::ExecAndRespondReMove(Message message, ServerPlayer aPlayer)
{
    if(game.ReMove(message.move.pos1, aPlayer.GetPlayer()))
    {
        char* buffer = "301";
        aPlayer.Send(buffer,3);

        char desbuf[12];
        char letter = (char) (message.move.pos1.letter + 'A');
        char num = message.move.pos1.number + '1';

        sprintf_s(desbuf,"403 %d %c%c", aPlayer.GetPlayer(), letter, num);

        // send the new move to every player
        player1.Send(desbuf,strlen(desbuf));
        player2.Send(desbuf,strlen(desbuf));
    }
    else
    {
        MoveErrorRespond(aPlayer);
    }
}

void GameSession::MoveErrorRespond(ServerPlayer aPlayer)
{
    if(aPlayer.GetPlayer() != game.GetPlayerTurn())
    {
        // not aPlayers turn
        char* buffer = "303";
        aPlayer.Send(buffer,3); 
    }
    else
    {
        // must be illegal move
        char* buffer = "302";
        aPlayer.Send(buffer,3); 
    }
}

void GameSession::UpdatePlayers()
{
    // check for new things that orccured, if
}