/*Copyright (c) 2012, winterdx <winterdx@gmail.com>

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.*/

#include "../block.h"
#include <cstring>

void fake_draw(std::list<Coord>, COLOR);

class Block_test : public Block {
    public:
        Block_test(int , int);
        int x() {return _x;}
        int y() {return _y;}
    private:
        const bool (*get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE];
        COLOR getcolor() const;
};

const bool (*Block_test::get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE] { return false; }
COLOR Block_test::getcolor() const { return GREY; }
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

    block1->draw(fake_draw);
    block2->draw(fake_draw);
    delete block1;
    delete block2;
    printf("Tests passed.\n");
    return 0;
}
void fake_draw(std::list<Coord>, COLOR) {}
