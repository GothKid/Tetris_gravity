#include "../block.h"
#include <cstring>

class Block_test : public Block {
    public:
        Block_test(int , int);
        int x() {return _x;}
        int y() {return _y;}
    private:
        const bool (*get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE];
};

const bool (*Block_test::get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE] {}
Block_test::Block_test(int x, int y) : Block() {
    _x = x;
    _y = y;
    memset(shape, 1, SHAPE_SIDE*SHAPE_SIDE);
}

int main() {
    Block_test *block1 = new Block_test(0, 0);
    Block_test *block2 = new Block_test(4, 3);

    block2->move_left();
    if (block2->x() != 4 || block2->y() != 3) {
        fprintf(stderr, "Error: Block moved left to collision. New position: (%d, %d)\n", block2->x(), block2->y());
        return 1;
    }
    block2->move_down();
    if (block2->x() != 4 || block2->y() != 4) {
        fprintf(stderr, "Error: Block didn't move down. New position: (%d, %d)\n", block2->x(), block2->y());
        return 1;
    }
    block1->move_right();
    if (block1->x() != 1 || block1->y() != 0) {
        fprintf(stderr, "Error: Block didn't move right. New position: (%d, %d)\n", block1->x(), block1->y());
        return 1;
    }
    block1->move_down();
    if (block1->x() != 1 || block1->y() != 0) {
        fprintf(stderr, "Error: Block moved down to collision. New position: (%d, %d)\n", block1->x(), block1->y());
        return 1;
    }

    block1->draw(TERM);
    block2->draw(TERM);
    delete block1;
    delete block2;
    printf("Tests passed.\n");
    return 0;
}
