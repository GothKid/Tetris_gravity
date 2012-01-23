#ifndef DRAW_H
#define DRAW_H
#include <list>

enum COLOR {GREY, CYAN, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED};
struct Coord {
    int x;
    int y;
};

typedef void (*Draw_func) (std::list<Coord>, COLOR);
#endif
