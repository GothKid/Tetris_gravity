#include "rectangle.h"

Rectangle::Rectangle(int x, int y, int height, int width) : Structure() {
    _x = x;
    _y = y;
    _height = height;
    _width = width;
}

bool Rectangle::occupied_at(int x, int y) const {
    return x >= _x && x < _x + _width && y >= _y && y < _y + _height;
}

void Rectangle::draw(Draw_func df) const {
    std::list<Coord> coords;
    for (int x = _x; x < _x + _width; ++x)
        for (int y = _y; y < _y + _height; ++y) {
            Coord c;
            c.x = x;
            c.y = y;
            coords.push_back(c);
        }
    df(coords, color);
}
