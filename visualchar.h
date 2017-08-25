#ifndef VISUALCHAR_H
#define VISUALCHAR_H

#include <list>
#include <memory>

enum class Color {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};



class VisualChar
{

public:
    char ch;
    Color color;
};

struct Coord
{
    int col;
    int row;
    bool operator ==(const Coord &cd2)
    {
        return col == cd2.col &&  row == cd2.row;
    }
};

class TreeCoord
{
public:
	int index = 0;

	TreeCoord(const Coord &coord, int iter);
	~TreeCoord();
	
	Coord cd = {0,0};
	int iteration = 0;

	TreeCoord * up = nullptr;
	std::list<TreeCoord *> elements;
	
	bool operator == (TreeCoord & tree)
	{
		return cd.col == tree.cd.col && cd.row == tree.cd.row;
	}
};


class TreeWay
{
public:
	TreeWay(TreeCoord& startTree);
	~TreeWay();

	bool push_back(TreeCoord *leaf, TreeCoord * newLeaf);


	TreeCoord tree;

	std::list<TreeCoord*> leafs;



private:

};


#endif // VISUALCHAR_H
