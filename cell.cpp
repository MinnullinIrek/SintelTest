#include "cell.h"

wchar_t knightChar = 'K';

Cell::Cell(wchar_t c):value(c)
{

}

wchar_t Cell::getChar()
{
    return (knight)? knightChar : value;
}

void Cell::setKnight(std::shared_ptr<Knight> _knight)
{
    knight = _knight;
}
