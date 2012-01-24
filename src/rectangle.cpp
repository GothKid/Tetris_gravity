/*Copyright (c) 2012, winterdx <winterdx@gmail.com>

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.*/

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

int Rectangle::min_x() const { return _x; }
int Rectangle::max_x() const { return _x + _width; }
int Rectangle::min_y() const { return _y; }
int Rectangle::max_y() const { return _y + _height; }
