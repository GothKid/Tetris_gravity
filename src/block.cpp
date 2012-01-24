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

#include "block.h"

Block *Block::_moving = 0;
Block::Block() : Structure() {
    for (int i = 0; i < SHAPE_SIDE*SHAPE_SIDE; ++i)
        shape[i] = false;
    _x = 1;
    _y = 0;
    _rotation = 0;
    _moving = this;
}

bool Block::occupied_at(int x, int y) const {
    //If the coordinates aren't in the shape, return false
    if (!is_possibly_occupied(x, y))
        return false;
    return shape[(y - _y) * SHAPE_SIDE + (x - _x)];
}


bool Block::collides(const Structure& other) const {
    //Check if collision is possible
    if (_x < other.x()) {
        if (max_x() < other.min_x())
            return false;
    } else {
        if (other.max_x() < min_x())
            return false;
    }
    if (_y < other.y()) {
        if (max_y() < other.min_y())
            return false;
    } else {
        if (other.max_y() < min_y())
            return false;
    }
    //For every cell occupied by the block, check if the other structucture
    //also occupies it
    for (int x = _x; x < _x + SHAPE_SIDE; ++x)
        for (int y = _y; y < _y + SHAPE_SIDE; ++y)
            if (occupied_at(x, y) && other.occupied_at(x, y))
                return true;
    return false;
}

bool Block::check_collides() const {
    for (std::list<Structure*>::const_iterator i = structures.begin();
            i != structures.end(); ++i) {
        if (!(*i))
            continue;
        if (*i != this && collides(**i))
            return true;
    }
    return false;
}
void Block::move_left() {
    --_x;
    if (check_collides())
        ++_x;
}
void Block::move_right() {
    ++_x;
    if (check_collides())
        --_x;
}
void Block::move_up() {
    --_y;
    if (check_collides())
        ++_y;
}
void Block::move_down() {
    ++_y;
    if (check_collides()) {
        if (_moving == this)
            _moving = 0;
        --_y;
        return;
    }
    _moving = this;
}

void Block::rotate() {
    int orig_rotation = _rotation;
    _rotation = (_rotation + 1) % 4;
    for (int i = 0; i < SHAPE_SIDE*SHAPE_SIDE; ++i)
        shape[i] = get_rotation_data()[_rotation][i];
    if (check_collides()) {
        _rotation = orig_rotation;
        for (int i = 0; i < SHAPE_SIDE*SHAPE_SIDE; ++i)
            shape[i] = get_rotation_data()[_rotation][i];
    }
}

bool Block::is_possibly_occupied(int x, int y) const {
    return x >= _x && x < _x + SHAPE_SIDE &&
        y >= _y && y < _y + SHAPE_SIDE;
}

bool Block::is_moving() {
    return _moving;
}

void Block::delete_row(int row) {
    //Check if the block is in the row
    if (row >= _y && row < _y + SHAPE_SIDE) {
        int block_row = row - _y;
        //Move the upper part of the figure
        for (;block_row > 0; --block_row)
            for (int i = 0; i < SHAPE_SIDE; ++i)
                shape[block_row*SHAPE_SIDE + i] = shape[(block_row-1)*SHAPE_SIDE + i];
        for (int i = 0; i < SHAPE_SIDE; ++i)
            shape[i] = 0;
    }
}

void Block::draw(Draw_func df) const {
    std::list<Coord> coords;
    for (int i = 0; i < SHAPE_SIDE; ++i)
        for (int j = 0; j < SHAPE_SIDE; ++j)
            if (shape[i*SHAPE_SIDE+j]) {
                Coord c;
                c.x = j + _x;
                c.y = i + _y;
                coords.push_back(c);
            }
    df(coords, getcolor());
}

bool Block::empty() const {
    for (int i = 0; i < SHAPE_SIDE*SHAPE_SIDE; ++i)
        if (shape[i])
            return false;
    return true;
}

int Block::min_x() const { return _x; }
int Block::max_x() const { return _x + SHAPE_SIDE; }
int Block::min_y() const { return _y; }
int Block::max_y() const { return _y + SHAPE_SIDE; }
