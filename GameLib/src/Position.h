#ifdef GAMELIB_EXPORTS
#define GAMELIB_API __declspec(dllexport) 
#else
#define GAMELIB_API __declspec(dllimport) 
#endif

#pragma once

namespace GameLib
{
    class Position{
    public:
        enum PosNum {ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN};
        enum PosLetter {A, B, C, D, E, F, G};
        PosLetter letter;
        PosNum number;

        GAMELIB_API Position(PosLetter aletter, PosNum anumber);
        GAMELIB_API Position();

        bool operator==(const Position& other);

        bool operator!=(const Position& other);
    };
}