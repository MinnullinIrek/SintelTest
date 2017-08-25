#include <iostream>
#include <memory>
#include <iostream>

using namespace std;

#include "visualizer.h"
#include "knight.h"
#include "board.h"
#include "mover.h"


int main()
{
	//cout << "Hello World!" << endl;
	try
	{
		shared_ptr<Board> board = make_shared<Board>(32);
		//board->randomMap();
		board->initMap(
			"........B...LLL.................\n"
			"........B...LLL.................\n"
			"........B...LLL...LLL...........\n"
			"........B...LLL..LLL...RR.......\n"
			"........B...LLLLLLLL...RR.......\n"
			"........B...LLLLLL..............\n"
			"........B............RR.........\n"
			"........BB...........RR.........\n"
			"......T.WBB.....................\n"
			"...RR...WWBBBBBBBBBB............\n"
			"...RR...WW.........B............\n"
			"........WW.........B......T.....\n"
			"...WWWWWWW.........B............\n"
			"...WWWWWWW.........B..RR........\n"
			"...WW..........BBBBB..RR.WWWWWWW\n"
			"...WW..........B.........W......\n"
			"WWWW...........B...WWWWWWW......\n"
			"...WWWWWWW.....B............BBBB\n"
			"...WWWWWWW.....BBB..........B...\n"
			"...WWWWWWW.......BWWWWWWBBBBB...\n"
			"...WWWWWWW.......BWWWWWWB.......\n"
			"...........BBB..........BB......\n"
			".....RR....B.............B......\n"
			".....RR....B.............B.T....\n"
			"...........B.....RR......B......\n"
			"...........B.....RR.............\n"
			"...........B..........RR........\n"
			"...........B..........RR........\n"
		);

		shared_ptr<Knight> knight = make_shared<Knight>();
		knight->setMover(make_unique<Mover>(board, knight, 0, 0));


		//Knight *knight = new Knight(board, 0, 0);
		shared_ptr<Visualizer> visualizer = make_shared<Visualizer>(board);
		knight->addWatcher([visualizer]() {visualizer->operator()(); });
		visualizer->printBoard(board); 
		 
		knight->moveTo(15, 3);

	}
	catch (exception &ex)
	{
		const char* ch = ex.what();
		std::cout << ex.what();

	}

    return 0;
}
