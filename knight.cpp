
#include "knight.h"
#include "mover.h"
#include "board.h"


using namespace std;

Knight::Knight(std::shared_ptr<Board> board, std::shared_ptr<Knight> knight,int col,int row):mover(std::make_unique<Mover>(board, std::shared_ptr<Knight>(this), col, row))
{


}

int Knight::moveTo(int col, int row)
{
    mover->moveTo(col, row);

}
