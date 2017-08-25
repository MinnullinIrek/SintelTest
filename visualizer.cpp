#include "visualizer.h"
#include <windows.h>
#include <thread>

#include "cell.h"
#include "board.h"

static LPDWORD logD = new DWORD;

Visualizer::Visualizer(std::shared_ptr<Board> board):board(board)
{
	for (auto & ihandle : handles)
		ihandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);;
	handle = handles.begin();
	setActiveBuffer(*handle);
	handle++;
    //handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Visualizer::printBoard(std::shared_ptr<Board> board)
{
    for(int col = 0; col < board->size; col ++){
        for(int row = 0; row < board->size; row++) {
            printCell(board->getCell(col, row), col, row);
        }
    }
	changeBuffer(); 
}

void Visualizer::operator()()
{
	clearRect(Region{0, 0, board->size, board->size }, ' ');
	printBoard(board);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	
}

void Visualizer::printCell(std::shared_ptr<Cell> cell, int col, int row)
{
    wchar_t ch = cell->getChar();
	if (ch == 'K')
		SetColor(Color::Yellow, Color::Black);
    WriteConsoleOutputCharacter(*handle, &ch, 1, COORD{(short)col, (short)row}, logD);
	SetColor(Color::White, Color::Black);
}

void Visualizer::SetColor( Color text, Color background)
{
    SetConsoleTextAttribute(*handle, (static_cast<WORD>(background) << 4) | static_cast<WORD>(text));
}
void Visualizer::clearRect(const Region &r, wchar_t empty)
{
    std::wstring ws(r.col2 - r.col1 + 1, empty);
    for (auto irow = r.row1; irow <= r.row2; irow++)
        WriteConsoleOutputCharacter(*handle, ws.c_str(), ws.length(), COORD{(short)r.col1, (short)irow}, logD);
}

void Visualizer::changeBuffer()
{
	setActiveBuffer(*handle);
	if (handle == handles.begin())
		++handle;
	else
		--handle;
}


void Visualizer::setActiveBuffer(HANDLE h)
{
	SetConsoleActiveScreenBuffer(h);
}