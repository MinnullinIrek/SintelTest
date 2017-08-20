#include "board.h"
#include "cell.h"

Board::Board(int size):size(size),
    map(size*size,
        [size](Coord &&cd){return size*cd.col + cd.row;},
        [](const Coord& lhs, const Coord& rhs) { return lhs.row == rhs.row && lhs.col == rhs.col; })
{

}

std::shared_ptr<Cell> Board::getCell(int col, int row)
{
    return map.at({col, row});
}

void Board::initMap(std::string strMap)
{
    int col =0;
    int row = 0;

    for (auto ch : strMap) {
        if (ch == '\n') {
            col = 0;
            row++;
        }
        else {
           map[Coord{col, row}] = std::make_shared<Cell>(ch);
           col ++;
        }

    }
}

void Board::randomMap()
{

}


