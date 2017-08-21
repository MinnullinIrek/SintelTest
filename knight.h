#ifndef KNIGHT_H
#define KNIGHT_H

#include <memory>
#include <functional>
#include <list>

class Mover;
class Board;


class Knight
{
	friend Mover;
    std::unique_ptr<Mover> mover;
	std::list<std::function<void()>> watchers;

	void informChanges();

public:
    Knight();

    int moveTo(int col, int row);

	void setMover(std::unique_ptr<Mover> newMover);

	void addWatcher(std::function<void()> watcher);

};

#endif // KNIGHT_H
