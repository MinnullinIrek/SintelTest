#ifndef VISUALIZER_H
#define VISUALIZER_H
#include <memory>
#include <windows.h>
#include <array>

#include "visualchar.h"

class Cell;
class Board;

struct Region
{
    int col1, row1, col2, row2;
};
using namespace std;

class Visualizer
{
	std::array<HANDLE, 2> handles;
	std::array<HANDLE, 2> ::iterator handle;

    void printCell(std::shared_ptr<Cell> cell, int col, int row);
    void clearRect(const Region &r, wchar_t empty);
	std::shared_ptr<Board> board; 

	void Visualizer::changeBuffer(); 
	void Visualizer::setActiveBuffer(HANDLE h);

public:
    Visualizer(std::shared_ptr<Board> board);
    void printBoard(std::shared_ptr<Board> board);
	void operator()();
	

};

#endif // VISUALIZER_H
