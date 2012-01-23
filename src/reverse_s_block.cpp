#include "block.h"

const bool Reverse_S_block::_rotation_data[4][SHAPE_SIDE*SHAPE_SIDE] = {
    {0, 0, 0, 0,
        0, 0, 0, 0,
        0, 1, 1, 0,
        0, 0, 1, 1},

    {0, 0, 0, 0,
        0, 0, 1, 0,
        0, 1, 1, 0,
        0, 1, 0, 0},

    {0, 0, 0, 0,
        0, 1, 1, 0,
        0, 0, 1, 1,
        0, 0, 0, 0},

    {0, 0, 0, 0,
        0, 0, 0, 1,
        0, 0, 1, 1,
        0, 0, 1, 0}};
Reverse_S_block::Reverse_S_block() : Block() {
    memcpy(shape, _rotation_data[_rotation], SHAPE_SIDE*SHAPE_SIDE);
}
COLOR Reverse_S_block::getcolor() const {
    return RED;
}

const bool (*Reverse_S_block::get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE] {
    return _rotation_data;
}
