#include "block.h"
#include "cstring"

Block::Block() {
    for (int i; i < SHAPE_SIDE*SHAPE_SIDE; ++i)
        shape[i] = false;
}

bool Block::occupied_at(int x, int y) const {
    //If the coordinates aren't in the sape, return false
    if (x - _x < 0 || x - _x >= SHAPE_SIDE ||
            y - _y < 0 || y - _y >= SHAPE_SIDE)
        return false;
    return shape[(y - _y) * SHAPE_SIDE + (x - _x)];
}


bool Block::collides(const Structure& other) const {
    for (int x = _y; x < SHAPE_SIDE; ++x)
        for (int y = _x; y < SHAPE_SIDE; ++y)
            if (occupied_at(x, y) && other.occupied_at(x, y))
                return true;
    return false;
}
