#include "cell.h"

wchar_t knightChar = 'K';

Cell::Cell(wchar_t c):value(c)
{

}

wchar_t Cell::getChar()
{
    return (knight)? knightChar : value;
}

void Cell::setChar(wchar_t ch)
{
	value = ch;
}

void Cell::setKnight(std::shared_ptr<Knight> _knight)
{
    knight = _knight;
}

void Cell::resetKnight()
{
	knight.reset();
}

int Cell::getStepCount()
{
	return stepCount;
}

void Cell::setStepCount(int stepCnt)
{
	stepCount = stepCnt;
}

bool Cell::getIsTeleport()
{
	return isTeleport;
}

void Cell::setIsTeleport(bool teleport)
{
	isTeleport = teleport;
}
