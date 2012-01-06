#include "block.h"
#include "cstring"

Block::Block() {
    for (int i; i < SHAPE_SIDE*SHAPE_SIDE; i++)
	shape[i] = false;
}

Collision Block::collides(const &block) {
    //See which block is on top
    Block top = (_x < block._x) ? *this : block;
    //See which block is on the left
    Block top = (_y < block._y) ? *this : block;
}
