#include "block.h"

Block::Block() : Structure() {
    for (int i; i < SHAPE_SIDE*SHAPE_SIDE; ++i)
        shape[i] = false;
    _rotation = 0;
    _is_moving = true;
}

bool Block::occupied_at(int x, int y) const {
    //If the coordinates aren't in the shape, return false
    if (!is_possibly_occupied(x, y))
        return false;
    return shape[(y - _y) * SHAPE_SIDE + (x - _x)];
}


bool Block::collides(const Structure& other) const {
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
            i != structures.end(); ++i)
        if (*i != this && collides(**i))
            return true;
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
        _is_moving = false;
        --_y;
    }
}

void Block::rotate() {
    _rotation = (_rotation + 1) % 4;
    for (int i = 0; i < SHAPE_SIDE*SHAPE_SIDE; ++i)
        shape[i] = get_rotation_data()[_rotation];
}

bool Block::is_possibly_occupied(int x, int y) const {
    return x >= _x && x < _x + SHAPE_SIDE &&
        y >= _y && y < _y + SHAPE_SIDE;
}

bool Block::is_moving() {
    return _is_moving;
}

void Block::delete_row(int row) {
    //Check if the block is in the row
    if (row >= _y && row < _y + SHAPE_SIDE) {
        int block_row = row - _y;
        for (int i = 0; i < SHAPE_SIDE; ++i)
            shape[block_row*SHAPE_SIDE + i] = 0;
    }
}

void Block::draw() const {
    for (int i = 0; i < SHAPE_SIDE; ++i)
        for (int j = 0; j < SHAPE_SIDE; ++j)
            if (shape[i*SHAPE_SIDE+j])
                fprintf(stderr, "Coord (%d, %d) occupied\n", _x + j, _y + i);
}

bool Block::empty() const {
    for (int i = 0; i < SHAPE_SIDE*SHAPE_SIDE; ++i)
        if (shape[i])
            return false;
    return true;
}
