#ifndef KNIGHT_H
#define KNIGHT_H
#include <memory>

class Mover;
class Board;

class Knight
{
    std::unique_ptr<Mover> mover;
public:
    Knight(std::shared_ptr<Board> board, std::shared_ptr<Knight> knight,int col,int row);

    int moveTo(int col, int row);


};

#endif // KNIGHT_H
