#include "visualchar.h"



TreeCoord::TreeCoord(const Coord & coord, int iter):cd(coord), iteration(iter)
{
}

TreeCoord::~TreeCoord()
{
}



TreeWay::TreeWay(TreeCoord& startTree): tree(startTree)
{
	leafs.push_back(&startTree);
}

TreeWay::~TreeWay()
{
}

bool TreeWay::push_back(TreeCoord *leaf,  TreeCoord * newLeaf)
{
	const TreeCoord * upper = leaf;
	bool exists = false;

	while (upper != nullptr) {
		if (upper->cd.col == newLeaf->cd.col && upper->cd.row == newLeaf->cd.row) {
			exists = true;
			break;
		}
		upper = upper->up;
	}

	if (!exists) {
		newLeaf->up = leaf;
		leaf->elements.push_back(newLeaf);
		leafs.push_back(newLeaf);
		return true;
	}

	return false;
}

