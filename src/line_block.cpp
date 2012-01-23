#include "block.h"

const bool Line_block::_rotation_data[4][SHAPE_SIDE*SHAPE_SIDE] = {
    {0, 0, 1, 0,
        0, 0, 1, 0,
        0, 0, 1, 0,
        0, 0, 1, 0},

    {0, 0, 0, 0,
        0, 0, 0, 0,
        1, 1, 1, 1,
        0, 0, 0, 0},

    {0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0,
        0, 1, 0, 0},

    {0, 0, 0, 0,
        1, 1, 1, 1,
        0, 0, 0, 0,
        0, 0, 0, 0}};
Line_block::Line_block() : Block() {
    memcpy(shape, _rotation_data[_rotation], SHAPE_SIDE*SHAPE_SIDE);
}
COLOR Line_block::getcolor() const {
    return CYAN;
}

const bool (*Line_block::get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE] {
    return _rotation_data;
}
