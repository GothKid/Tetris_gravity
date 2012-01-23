
#include "block.h"

const bool S_block::_rotation_data[4][SHAPE_SIDE*SHAPE_SIDE] = {
    {0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 1, 1,
        0, 1, 1, 0},

    {0, 0, 0, 0,
        0, 1, 0, 0,
        0, 1, 1, 0,
        0, 0, 1, 0},

    {0, 0, 0, 0,
        0, 0, 1, 1,
        0, 1, 1, 0,
        0, 0, 0, 0},

    {0, 0, 0, 0,
        0, 0, 1, 0,
        0, 0, 1, 1,
        0, 0, 0, 1}};
S_block::S_block() : Block() {
    memcpy(shape, _rotation_data[_rotation], SHAPE_SIDE*SHAPE_SIDE);
}
COLOR S_block::getcolor() const {
    return GREEN;
}

const bool (*S_block::get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE] {
    return _rotation_data;
}
