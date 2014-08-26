#ifdef GAMELIB_EXPORTS
#define GAMELIB_API __declspec(dllexport) 
#else
#define GAMELIB_API __declspec(dllimport) 
#endif

#pragma once

#include <Windows.h>
#include "Position.h"
#include <string>

namespace GameLib
{
    POINT CalculateDrawPoint(Position position);

    GAMELIB_API Position CreatePos(char letter, int num);
}