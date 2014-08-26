#include "Position.h"
#include "stdafx.h"

namespace GameLib
{
Position::Position(PosLetter aletter, PosNum anumber)
{
    letter = aletter;
    number = anumber;
}

Position::Position()
{

}
 
// overload comparison for nodes
bool Position::operator==(const Position& other)
{
    // check that numbers are equal and letters are equal
    return (other.letter == letter && other.number == number);
}

bool Position::operator!=(const Position& other)
{
    return !(other.letter == letter && other.number == number);
}
}