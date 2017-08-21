#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <memory>
#include <windows.h>

#include "visualchar.h"

class Cell;
class Board;

struct Region
{
    int col1, row1, col2, row2;
};
using namespace std;

//WriteConsoleOutputCharacter(h, str.c_str() + current, min(len - current, delta), COORD{ r.col1, irow }, logD);
class Visualizer
{
    HANDLE handle;

    void printCell(std::shared_ptr<Cell> cell, int col, int row);
    void SetColor(Color text, Color background);
    void clearRect(const Region &r, wchar_t empty);
	std::shared_ptr<Board> board;
public:
    Visualizer(std::shared_ptr<Board> board);
    void printBoard(std::shared_ptr<Board> board);
	void operator()();
	

};

#endif // VISUALIZER_H
