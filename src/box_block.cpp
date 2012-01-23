#include "block.h"

const bool Box_block::_rotation_data[4][SHAPE_SIDE*SHAPE_SIDE] = {
    {0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 1, 1,
        0, 0, 1, 1},

    {0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 1, 1,
        0, 0, 1, 1},

    {0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 1, 1,
        0, 0, 1, 1},

    {0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 1, 1,
        0, 0, 1, 1}};

Box_block::Box_block() : Block() {
    memcpy(shape, _rotation_data[_rotation], SHAPE_SIDE*SHAPE_SIDE);
}
COLOR Box_block::getcolor() const {
    return YELLOW;
}

const bool (*Box_block::get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE] {
    return _rotation_data;
}
