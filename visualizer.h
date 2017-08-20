#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <memory>
#include <windows.h>

#include "visualchar.h"

class Cell;
class Board;

struct Region
{
    short col1, row1, col2, row2;
};
using namespace std;

//WriteConsoleOutputCharacter(h, str.c_str() + current, min(len - current, delta), COORD{ r.col1, irow }, logD);
class Visualizer
{
    HANDLE handle;

    void printCell(std::shared_ptr<Cell> cell, int col, int row);
    void SetColor(Color text, Color background);
    void clearRect(const Region &r, wchar_t empty);
public:
    Visualizer();
    void printBoard(std::shared_ptr<Board> board);

};

#endif // VISUALIZER_H
