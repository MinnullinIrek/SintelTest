#include <random>
#include <exception>

#include "board.h"
#include "cell.h"


Board::Board(int size):size(size),
    map(size*size,
        [size](Coord &&cd){return size*cd.col + cd.row;},
        [](const Coord& lhs, const Coord& rhs) { return lhs.row == rhs.row && lhs.col == rhs.col; })
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			map[{i, j}] = std::make_shared<Cell>();
		}
}

std::shared_ptr<Cell> Board::getCell(int col, int row)
{
    return map.at({col, row});
}

std::list<Coord> Board::getTeleports()
{
	return teleports;
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
		   auto cell = map[Coord{ col, row }];
		   cell->setChar(ch);

		   switch (ch)
		   {
		   case '.':
			   cell->setStepCount(1);
			   break;
		   case 'W':
			   cell->setStepCount(2);
			   break;
		   case 'L':
			   cell->setStepCount(5);
			   break;
		   case 'R':
			   cell->setStepCount(-1);
			   break;
		   case 'B':
			   cell->setStepCount(-2);
			   break;
		   case 'T':
			   cell->setStepCount(1);
			   cell->setIsTeleport(true);
			   teleports.push_back({ col, row });
			   break;
		   default:
			   throw std::runtime_error((std::string("unexcepted char ") + ch).c_str());
		   }

           //map[Coord{col, row}] = std::make_shared<Cell>(ch);
           col ++;
        }

    }
}

void Board::randomMap()
{
	std::random_device rd;
	std::default_random_engine dre(rd());

	auto rand = std::uniform_int_distribution<int>(-40, 20);
	int count = 0;
	for (auto cell :  map) {
		auto i = rand(dre);
		count++;

		if (i < 10)
		{
			cell.second->setChar('.');
			cell.second->setStepCount(1);
		}
		else if(i < 15)
		{
			cell.second->setChar('W');
			cell.second->setStepCount(2);
		}
		else if (i < 17)
		{
			cell.second->setChar('L');
			cell.second->setStepCount(5);
		}
		else if (i < 19)
		{
			cell.second->setChar('R');
			cell.second->setStepCount(-1);
		}
		else if (i == 19)
		{
			cell.second->setChar('B');
			cell.second->setStepCount(-2);
		}
		else if(i == 20)
		{
			cell.second->setChar('T');
			cell.second->setStepCount(1);
			cell.second->setIsTeleport(true);
			teleports.push_back({ size - (int)(count / size) - 1, count / size });
		}

	}



}


