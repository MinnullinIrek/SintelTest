#include <list>

#include "mover.h"
#include "board.h"
#include "knight.h"
#include "cell.h"

Mover:: Mover(std::shared_ptr<Board> board, std::shared_ptr<Knight> knight, int col,int row):
    startCol(col),
    startRow(row),
    board(board),
    knight(knight),
    curCell(board->getCell(col, row)),
    mp(board->size * board->size,
       [this](Coord &&cd){return this->board->size*cd.col + cd.row;},
       [](const Coord& lhs, const Coord& rhs) { return lhs.row == rhs.row && lhs.col == rhs.col; })
{
	curCell->setKnight(knight);
	curCell->setChar('S');

	checkers.push_back([this](const Coord& cd1, const Coord& cd)
	{
		return cd.col > 0 &&
			cd.row > 0 &&
			cd.col < this->board->size &&
			cd.row < this->board->size;
	});

	checkers.push_back([this](const Coord&, const Coord& cd) {return mp[cd].first == 0; });
	checkers.push_back([this](const Coord&, const Coord& cd) {return this->board->getCell(cd.col, cd.row)->getStepCount() >= 0; });
	checkers.push_back([this](const Coord& cd1, const Coord& cd)
	{
		auto cells = getCellsBetweenCoords(cd1, cd);
		for (auto cell : cells)
			if (cell->getStepCount() == -2)
				return false;
		return true;
	});

}

int Mover::moveTo(int col, int row)
{
	auto targetCell = board->getCell( col, row );
	if (targetCell->getStepCount() < 0 || (col == startCol && row == startRow)) {
		return 0;
	}
	board->getCell(col, row)->setChar('E');
	int iteration = 0;
	mp[{startCol, startRow}].first = iteration;

	std::list< std::pair<Coord, int>> positions = { std::make_pair<Coord, int>({ startCol, startRow}, 1)};
	std::list<std::pair<Coord, int>> nextPositions;
	
	auto checker = [this](const Coord& cdStart, const Coord& cdEnd)
	{
		for (auto & checkFunc : this->checkers)
			if (!checkFunc(cdStart, cdEnd))
				return false;
		return true;
	};

	while (true) {
		iteration++;
		for (auto pos : positions) {
			if(pos.second == iteration) {
				auto lst = getPossibleMoves(pos.first.col, pos.first.row, iteration, checker);

				for (auto cd : lst) {
					mp[{cd.first.col, cd.first.row}].first = iteration;
					mp[{cd.first.col, cd.first.row}].second = { pos.first.col, pos.first.row };
					if (cd.first.col == col && cd.first.row == row) {
						moveByWay(getBackWay(std::move(cd.first)));
						goto brek;
					}
				}
				nextPositions.insert(nextPositions.end(), lst.begin(), lst.end());
			}
			else { 
				nextPositions.push_back(pos);
			}
		}
		positions = nextPositions;
		nextPositions.clear();
	}

	brek:
	return iteration;
}

Coord Mover::getHorseCoords(int c, int r, int count)
{
    int d = 3;
    int dx = 1;//2
    int i1 = 1;//-1
    int i2 = 1;//-1

    switch (count) {
    case 1:
        i1 = 1;
        i2 = 1;
        dx = 1;
        break;
    case 2:
        i1 = -1;
        i2 = -1;
        dx = 1;
        break;
    case 3:
        i1 = 1;
        i2 = -1;
        dx = 1;
        break;
    case 4:
        i1 = -1;
        i2 = 1;
        dx = 1;
        break;
    case 5:
        i1 = 1;
        i2 = 1;
        dx = 2;
        break;
    case 6:
        i1 = -1;
        i2 = -1;
        dx = 2;
        break;
    case 7:
        i1 = 1;
        i2 = -1;
        dx = 2;
        break;
    case 8:
        i1 = -1;
        i2 = 1;
        dx = 2;
        break;
    default:
        break;
    }

    return Coord{c + i1 * (dx), r + i2 * (d - dx)};
}



std::list<Coord> Mover::getBackWay(const Coord &cd)
{
	int itertion = mp[cd].first;
	std::list<Coord> backWay = {cd};

	
	Coord last = cd;
	while(last.col != startCol && last.row != startRow) {
		itertion--;
		Coord newCoord = mp[last].second;
		backWay.push_front(newCoord);
		last = newCoord;
	}

	return backWay;
}

bool Mover::moveByWay(std::list<Coord> coords)
{
	if (checkMoves(coords)) {
		for (auto cd : coords) {
			moveLikeKnight(std::move(cd));
		}
		return true;
	}
	return false;
}

bool Mover::checkMoves(const std::list<Coord>& coords)
{
	Coord cdLast = {-1, -1};

	for (auto cd : coords) {
		if (cdLast.col != -1 && cdLast.row != -1) {
			int deltaRow = abs(cdLast.row - cd.row);
			int deltaCol = abs(cdLast.col - cd.col);

			if (!((deltaRow == 2 && deltaCol == 1) || (deltaRow == 1 && deltaCol == 2))) {
				if (!board->getCell(cd.col, cd.row)->getIsTeleport()) {
					return false;
				}
			}
		}
		cdLast = cd;
	}

	return true;
}

void Mover::moveLikeKnight(Coord &&cd)
{

	curCell->resetKnight();
	curCell.swap(board->getCell(cd.col, cd.row));
	curCell->setKnight(knight);
	knight->informChanges();

	this->startCol = cd.col;
	this->startRow = cd.row;
}

std::list<std::shared_ptr<Cell>> Mover::getCellsBetweenCoords(const Coord & cd1, const Coord & cd2)
{
	std::list<std::shared_ptr<Cell>> cells;

	if (abs(cd1.col - cd2.col) >  abs(cd1.row - cd2.row)) {
		cells.push_back(board->getCell((cd1.col + cd2.col)/2, cd1.row));
		cells.push_back(board->getCell(cd2.col , cd1.row));
	}
	else {
		cells.push_back(board->getCell(cd1.col, (cd1.row + cd2.row) / 2));
		cells.push_back(board->getCell(cd1.col, cd2.row));
	}
	cells.push_back(board->getCell(cd2.col, cd2.row));

	return cells;
}

void Mover::cycler(int stCol, int stRow,std::function<bool(Coord&)> cycle)
{
	for (int i = 1; i <= 8; i++) {
		auto cd = getHorseCoords(stCol, stRow, i);
		if (! cycle(cd)) {
			break;
		}
	}
}

std::list<std::pair<Coord, int>> Mover::getPossibleMoves(int stCol, int stRow, int iteration, Checker checker)
{
    std::list<std::pair<Coord, int>> coords;
	cycler(stCol, stRow, 
		[this, &coords, &checker, stCol, stRow, iteration](Coord& cd)
		{
			if (checker({ stCol, stRow }, cd)) {
				coords.push_back(std::make_pair<Coord, int>(std::move(cd), std::move(iteration + board->getCell(cd.col, cd.row)->getStepCount())));
				auto cell = board->getCell(cd.col, cd.row);
				if (board->getCell(cd.col, cd.row)->getIsTeleport()) {
					auto teleports = board->getTeleports();
					for (auto teleportCoord : teleports) {
						coords.push_back(std::make_pair(std::move(teleportCoord), std::move(iteration + board->getCell(cd.col, cd.row)->getStepCount())));
					}
				}
			}
			return true;
		});

     return coords;
}
