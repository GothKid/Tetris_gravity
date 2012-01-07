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

void Rectangle::draw() const {
}
