#include "Util.h"
#include "stdafx.h"


namespace GameLib
{
    POINT CalculateDrawPoint(GameLib::Position position)
    {
        //TODO fix magic number 6, 10 and 400

        // board i from bottom right to top left, there fore start number at 7-number, i.e 1 is down 
        POINT p = POINT();
        float dx = ((float) (position.letter)) / 6;

        float dy = ((float) (6 - position.number)) / 6 ;

        p.x = (int) (400 * dx) + 10;
        p.y = (int) (400 * dy) + 10;

        return p;
    }


    // create a position from letter and int, assume aletter is from capital and from A to G and num is from 1 to 9
    Position CreatePos(char aletter, int num)
    {
        Position::PosLetter let;

        switch (aletter)
        {
        case 'A':            
            let = Position::A;
            break;
        case 'B':
            let = Position::B;
            break;
        case 'C':
            let = Position::C;
            break;
        case 'D':
            let = Position::D;
            break;
        case 'E':
            let = Position::E;
            break;
        case 'F':
            let = Position::F;
            break;
        case 'G':
            let = Position::G;
            break;
        default:
            break;
        }

        return Position(let,(Position::PosNum) num);       
    }


}