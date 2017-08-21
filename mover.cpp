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
}

int Mover::moveTo(int col, int row)
{
	int iteration = 0;
	mp[{startCol, startRow}] = iteration;

	std::list< std::pair<Coord, int>> positions = { std::make_pair<Coord, int>({ startCol, startRow}, 1)};
	std::list<std::pair<Coord, int>> nextPositions;

	while (true)
	{
		iteration++;
		for (auto pos : positions) {
			if(pos.second == iteration)
			{
				auto lst = getPossibleMoves(pos.first.col, pos.first.row, iteration);


				for (auto cd : lst) {
					mp[cd.first] = iteration;
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

Coord Mover::getPair(int c, int r, int count)
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

bool Mover::checkCoord(const Coord& cd)
{
    return  cd.col > 0 &&
            cd.row > 0 &&
            cd.col < board->size &&
            cd.row < board->size &&
            mp[cd] == 0 &&
			board->getCell(cd.col, cd.row)->getStepCount() >= 0		
		;
}

std::list<Coord> Mover::getBackWay(Coord &&cd)
{
	int itertion = mp[cd];
	std::list<Coord> backWay;
	while(itertion > 0) {
		itertion--;
		for (auto i = 1; i <= 8; i++) {
			auto coord = getPair(cd.col, cd.row, i);
			if (mp[coord] == itertion) {
				backWay.push_front(coord);
				cd = coord;
				break;
			}
		}
	}

	return backWay;
}

void Mover::moveByWay(std::list<Coord> coords)
{
	for (auto cd : coords) {
		moveLikeKnight(std::move(cd));
		
	}
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

std::list<std::pair<Coord, int>> Mover::getPossibleMoves(int startCol, int startRow, int iteration)
{
    std::list<std::pair<Coord, int>> coords;

    for (int i = 1; i <= 8; i++) {
        auto cd = getPair(startCol, startRow, i);

		if (checkCoord(std::move(cd))) {
			coords.push_back(std::make_pair<Coord, int>(std::move(cd), std::move(iteration + board->getCell(cd.col, cd.row)->getStepCount())));
		}
    }

    return coords;
}
