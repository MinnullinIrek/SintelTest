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

	while (true) {
		iteration++;
		for (auto pos : positions) {
			if(pos.second == iteration) {
				auto lst = getPossibleMoves(pos.first.col, pos.first.row, iteration, [this](const Coord& cd1, const Coord& cd) {return checkCoord(cd1, cd); });

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

int Mover::findLongestWay(int col, int row)
{
	std::list< std::pair<std::list<std::pair<Coord, int>>, int> > ways = { { {{{startCol, startRow},0}}, 0 } };

	
	int deleteFirst = 0;
	int i = 0;
	
	for (auto &way : ways) {
		
		if (i >= ways.size())
		{
			break;
		}
		int iteration = way.second;

		for (; deleteFirst > 0; deleteFirst --)
		{
			ways.pop_front();
			
		}

		

		auto &coord = way.first.back();
		{
			if (coord.second == iteration) {
				auto lst = getPossibleMoves(coord.first.col, coord.first.row, iteration, [this, &way](const Coord &cd1, const Coord &cd)
				{
					if (cd.col > 0 &&
						cd.row > 0 &&
						cd.col < board->size &&
						cd.row < board->size &&
						board->getCell(cd.col, cd.row)->getStepCount() >= 0)
					{
						auto cells = get—ellsBetweenCoords(cd1, cd);
						for (auto cell : cells)
							if (cell->getStepCount() == -2)
								return false;

						for (auto coord : way.first) {
							if (cd.col == coord.first.col && cd.row == coord.first.row) {
								return false;
							}
						}

						return true;
					}
					return false;
				}
				);

				if (!lst.empty()) {
					i=0;
					//ways.remove(way);
					deleteFirst ++;
					
					for (auto cd : lst) {
						auto newWay = way;
						newWay.first.push_back(cd);
						newWay.second++;
						ways.push_back(newWay);
					}

					//ways.pop_front();
				}
				else
				{
					i++;
					auto newWay = way;
					newWay.second++;
					deleteFirst++;
					ways.push_back(way);
				}
			}
		}
		
	}
	
	auto longestWay = ways.begin();

	for (decltype(ways)::iterator way = ways.begin(); way != ways.end(); ++way) {

		//int stepCount = 0;


		if (way->first.size() > longestWay->first.size()) {
			longestWay = way;
		}


	}

	std::list<Coord> lWay;
	for (auto way : longestWay->first) {
		lWay.push_back(way.first);
	}

	moveByWay(lWay);


	return 0;
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

bool Mover::checkCoord(const Coord& cd1, const Coord& cd)
{
	if (cd.col > 0 &&
		cd.row > 0 &&
		cd.col < board->size &&
		cd.row < board->size &&
		mp[cd] == 0 &&
		board->getCell(cd.col, cd.row)->getStepCount() >= 0)
	{
		auto cells = get—ellsBetweenCoords(cd1, cd);
		for (auto cell : cells)
			if (cell->getStepCount() == -2)
				return false;
		return true;
	}
	
	return false;
}

std::list<Coord> Mover::getBackWay(Coord &&cd)
{
	int itertion = mp[cd];
	std::list<Coord> backWay;
	auto findPrevCoord = [&backWay, this, &cd](int iteration, Coord &cord) {
		bool didFind = false;
		for (auto i = 1; i <= 8; i++) {
			auto coord = getPair(cord.col, cord.row, i);
			if (coord.col >= 0 && coord.row >= 0 && mp[coord] == iteration) {
				backWay.push_front(coord);
				cd = coord;
				didFind = true;
				break;
			}
		}

		return didFind;
	};
	
	while(itertion > 0) {
		itertion--;
		bool didFind = findPrevCoord(itertion, cd);

		if (!didFind)
		{
			auto lastCellCoord = backWay.front();

			auto lastCell = board->getCell(lastCellCoord.col, lastCellCoord.row);

			if (lastCell->getIsTeleport())
			{
				auto teleportsCoordsList = board->getTeleports();

				for (auto teleport : teleportsCoordsList) {
					if (findPrevCoord(itertion, teleport))
						break;
				}
			}
			else
			{
				throw std::runtime_error("cant find backWay");
			}
		}
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

				//auto cellLast = board->getCell(cdLast.col, cdLast.row);
				auto cell = board->getCell(cd.col, cd.row);
				
				if (! cell->getIsTeleport()) {
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

std::list<std::shared_ptr<Cell>> Mover::get—ellsBetweenCoords(const Coord & cd1, const Coord & cd2)
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

std::list<std::pair<Coord, int>> Mover::getPossibleMoves(int startCol, int startRow, int iteration, std::function<bool(const Coord&, const Coord&)> coordChecker)
{
    std::list<std::pair<Coord, int>> coords;

    for (int i = 1; i <= 8; i++) {
        auto cd = getPair(startCol, startRow, i);

		if (coordChecker({startCol, startRow}, cd)) {
			coords.push_back(std::make_pair<Coord, int>(std::move(cd), std::move(iteration + board->getCell(cd.col, cd.row)->getStepCount())));
			if (board->getCell(cd.col, cd.row)->getIsTeleport()) {
				auto teleports = board->getTeleports();
				for (auto teleportCoord : teleports) {
					coords.push_back(std::make_pair(std::move(teleportCoord), std::move(iteration + board->getCell(cd.col, cd.row)->getStepCount())));
				}
			}
		}


    }

    return coords;
}
