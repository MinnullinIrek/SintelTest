
#include "knight.h"
#include "mover.h"
#include "board.h"


using namespace std;

void Knight::informChanges()
{	
	for (auto watcher: watchers) {
		watcher();
	}
}

Knight::Knight()
{
} 

int Knight::moveTo(int col, int row)
{ 
    return mover->moveTo(col, row);

}

void Knight::setMover(std::unique_ptr<Mover> newMover)
{
	mover.swap(newMover);
}

void Knight::addWatcher(std::function<void()> watcher)
{
	watchers.push_back(watcher);
}
