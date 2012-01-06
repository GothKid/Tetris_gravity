#include "block.h"

Block::Block() : Structure() {
    for (int i; i < SHAPE_SIDE*SHAPE_SIDE; ++i)
        shape[i] = false;
    _rotation = 0;
}

bool Block::occupied_at(int x, int y) const {
    //If the coordinates aren't in the sape, return false
    if (x - _x < 0 || x - _x >= SHAPE_SIDE ||
            y - _y < 0 || y - _y >= SHAPE_SIDE)
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
    if (check_collides())
        --_y;
}

void Block::rotate() {
    _rotation = (_rotation + 1) % 4;
    for (int i = 0; i < SHAPE_SIDE*SHAPE_SIDE; ++i)
        shape[i] = get_rotation_data()[_rotation];
}
