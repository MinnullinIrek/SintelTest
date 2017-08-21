#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include <list>


#include "visualchar.h"
class Cell;





using Map = std::unordered_map<Coord, std::shared_ptr<Cell>, std::function<int(Coord)>,std::function<int(Coord cd1, Coord cd2)> >;


class Board
{
    Map map;

	std::list<Coord> teleports;
public:
    Board(int size);
    void initMap(std::string strMap);
    void randomMap();
    std::shared_ptr<Cell> getCell(int col, int row);

	std::list<Coord> getTeleports();

    const int size ;

	

};

#endif // BOARD_H
