#ifndef CELL_H
#define CELL_H

#include <memory>
class Knight;

class Cell
{
    wchar_t value;
    std::shared_ptr<Knight> knight;
public:
    Cell(wchar_t c);
    wchar_t getChar();
    void setKnight(std::shared_ptr<Knight> knight);

};

#endif // CELL_H
