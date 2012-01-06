#include "../block.h"
#include <cstring>

class Block_test : public Block {
    public:
        Block_test(int , int , const std::list<Structure*> &);
        int x() {return _x;}
        int y() {return _y;}
};

Block_test::Block_test(int x, int y, const std::list<Structure*> &s) : Block(s) {
    _x = x;
    _y = y;
    memset(shape, 1, SHAPE_SIDE*SHAPE_SIDE);
}

int main() {
    std::list<Structure*> blocks;
    Block_test block1(0, 0, blocks);
    Block_test block2(4, 3, blocks);
    blocks.push_back(&block1);
    blocks.push_back(&block2);

    block2.move_left();
    if (block2.x() != 4 || block2.y() != 3) {
        fprintf(stderr, "Error: Block moved left to collision. New position: (%d, %d)\n", block2.x(), block2.y());
        return 1;
    }
    block2.move_down();
    if (block2.x() != 4 || block2.y() != 4) {
        fprintf(stderr, "Error: Block didn't move down. New position: (%d, %d)\n", block2.x(), block2.y());
        return 1;
    }
    block1.move_right();
    if (block1.x() != 1 || block1.y() != 0) {
        fprintf(stderr, "Error: Block didn't move right. New position: (%d, %d)\n", block1.x(), block1.y());
        return 1;
    }
    block1.move_down();
    if (block1.x() != 1 || block1.y() != 0) {
        fprintf(stderr, "Error: Block moved down to collision. New position: (%d, %d)\n", block1.x(), block1.y());
        return 1;
    }
    return 0;
}
