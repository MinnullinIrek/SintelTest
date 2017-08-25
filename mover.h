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
using Checker = std::function<bool(const Coord&, const Coord&)>;

class Mover
{
    int startCol;
    int startRow;
    std::shared_ptr<Knight> knight;
    std::shared_ptr<Board> board;
    std::shared_ptr<Cell> curCell;
    std::unordered_map<Coord, std::pair<int, Coord>, std::function<int(Coord)>, std::function<int(Coord cd1, Coord cd2)>> mp;
	std::list<Checker> checkers;
private:
	std::list<std::pair<Coord, int>> getPossibleMoves(int startCol, int startRow, int iteration, Checker checker);

    Coord getHorseCoords(int c, int r, int count);

	std::list<Coord> getBackWay(const Coord & cd);
	bool moveByWay(std::list<Coord> coords);

	bool checkMoves(const std::list<Coord>& coords);

	void moveLikeKnight(Coord &&cd);
	std::list<std::shared_ptr<Cell>> getCellsBetweenCoords(const Coord & cd1, const Coord & cd2);

	void cycler(int stCol, int stRow, std::function<bool(Coord&)> cycle);


public:
    Mover(std::shared_ptr<Board> board, std::shared_ptr<Knight> knight,int col,int row);

    int moveTo(int col, int row);
	 
}; 

#endif // MOVER_H
