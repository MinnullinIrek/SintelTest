#ifndef MOVER_H
#define MOVER_H

#include <memory>
#include <list>
#include <unordered_map>
#include <functional>

#include "visualchar.h"


class Cell;
class Board;
class Knight;


class Mover
{
    int startCol;
    int startRow;
    std::shared_ptr<Knight> knight;
    std::shared_ptr<Board> board;
    std::shared_ptr<Cell> curCell;
    std::unordered_map<Coord, int, std::function<int(Coord)>, std::function<int(Coord cd1, Coord cd2)>> mp;

private:
	std::list<std::pair<Coord, int>> getPossibleMoves(int startCol, int startRow, int iteration);
    Coord getPair(int c, int r, int count);
    bool checkCoord(Coord && cd);

	std::list<Coord> getBackWay(Coord && cd);
	void moveByWay(std::list<Coord> coords);
	void moveLikeKnight(Coord &&cd);

public:
    Mover(std::shared_ptr<Board> board, std::shared_ptr<Knight> knight,int col,int row);

    int moveTo(int col, int row);

};

#endif // MOVER_H
