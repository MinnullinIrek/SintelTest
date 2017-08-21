#include <iostream>
#include <memory>
using namespace std;

#include "visualizer.h"
#include "knight.h"
#include "board.h"
#include "mover.h"


int main()
{
    //cout << "Hello World!" << endl;

	shared_ptr<Board> board = make_shared<Board>(32);
	board->randomMap();

	shared_ptr<Knight> knight = make_shared<Knight>();
	knight->setMover(make_unique<Mover>(board, knight, 0, 0));


	//Knight *knight = new Knight(board, 0, 0);
	shared_ptr<Visualizer> visualizer = make_shared<Visualizer>(board);
	knight->addWatcher([visualizer]() {visualizer->operator()(); });
	visualizer->printBoard(board);

	knight->moveTo(10, 5);



	

    return 0;
}
