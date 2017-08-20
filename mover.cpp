#include "mover.h"

#include "board.h"
#include "knight.h"
#include "cell.h"

Mover:: Mover(std::shared_ptr<Board> board, std::shared_ptr<Knight> knight, int col,int row):
    col(col),
    row(row),
    board(board),
    knight(knight),
    curCell(board->getCell(col, row)),
    mp(board->size * board->size,
       [this](Coord &&cd){return this->board->size*cd.col + cd.row;},
       [](const Coord& lhs, const Coord& rhs) { return lhs.row == rhs.row && lhs.col == rhs.col; })
{

}

int Mover::moveTo(int col, int row)
{


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

bool Mover::checkCoord(Coord&& cd)
{
    return  cd.col > 0 &&
            cd.row > 0 &&
            cd.col < board->size &&
            cd.row < board->size &&
            mp[cd] == 0;
}

std::list<Coord> Mover::getPossibleMoves(int startCol, int startRow)
{
    std::list<Coord> coords;

    for (int i = 1; i <= 8; i++) {
        Coord cd = getPair(startCol, startRow, i);

        if(checkCoord(std::move(cd)))
            coords.push_back(cd);
    }

    return coords;
}
