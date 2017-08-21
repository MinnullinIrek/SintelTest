#ifndef CELL_H
#define CELL_H

#include <memory>
class Knight;

class Cell
{
    wchar_t value;
    std::shared_ptr<Knight> knight;
	int stepCount = 1;
	bool isTeleport = false;
public:
    Cell(wchar_t c = '.');
    
	wchar_t getChar();
	void setChar(wchar_t ch);
    void setKnight(std::shared_ptr<Knight> knight);
	void resetKnight();
	int getStepCount();
	void setStepCount(int stepCnt);

	bool getIsTeleport();
	void setIsTeleport(bool teleport);

};

#endif // CELL_H
