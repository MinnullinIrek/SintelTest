#ifndef VISUALCHAR_H
#define VISUALCHAR_H

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
 
#endif // VISUALCHAR_H
 