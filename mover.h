#ifndef MOVER_H
#define MOVER_H

#include <memory>
#include <list>
#include <unordered_map>

#include "visualchar.h"


class Cell;
class Board;
class Knight;


class Mover
{
    int col;
    int row;
    std::shared_ptr<Knight> knight;
    std::shared_ptr<Board> board;
    std::shared_ptr<Cell> curCell;
    std::unordered_map<Coord, std::shared_ptr<Cell>, std::function<int(Coord)>,std::function<int(Coord cd1, Coord cd2)>> mp;

private:
    std::list<Coord> getPossibleMoves(int startCol, int startRow);
    Coord getPair(int c, int r, int count);
    bool checkCoord(Coord && cd);

public:
    Mover(std::shared_ptr<Board> board, std::shared_ptr<Knight> knight,int col,int row);

    int moveTo(int col, int row);
};

#endif // MOVER_H
