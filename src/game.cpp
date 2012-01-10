#include "game.h"
#include "block.h"
#include "rectangle.h"
#include <cstdlib>
#include <ctime>

typedef std::list<Block*>::iterator block_iter;
const int HEIGHT = 20;
const int WIDTH = 8;
void ini_blocks() {
#ifdef __APPLE__
    srandom(time(0));
#else
    srand(time(0));
#endif
    new Rectangle(0, 0, HEIGHT, 1);
    new Rectangle(WIDTH+1, 0, HEIGHT, 1);
    new Rectangle(1, HEIGHT+1, 1, WIDTH);
} 

void clean_rows(std::list<Block*> blocks) {
    for (int i = 0; i <= HEIGHT; ++i) {
        int occupied = 0;
        for (int j = 1; j <= WIDTH; ++j) {
            for (block_iter iter = blocks.begin(); iter != blocks.end(); ++iter) {
                if ((*iter)->occupied_at(j, i)) 
                    ++occupied;
            }
        }
        if (occupied == WIDTH)
            for (block_iter iter = blocks.begin(); iter != blocks.end(); ++iter)
                (*iter)->delete_row(i);
    }
}

void delete_empty_blocks(std::list<Block*> blocks) {
    for (block_iter iter = blocks.begin(); iter != blocks.end(); ++iter) {
        if ((*iter)->empty()) {
            delete *iter;
            iter = blocks.erase(iter);
        }
    }
}

void advance_blocks(std::list<Block*> blocks) {
    for (block_iter iter = blocks.begin(); iter != blocks.end(); ++iter)
        (*iter)->move_down();
}

Block *new_block() {
#ifdef __APPLE__
    int block_type = random() % 7;
#else
    int block_type = rand() % 7;
#endif
    Block * bl;
    switch (block_type) {
        case 0:
            bl = new Line_block;
            break;
        case 1:
            bl = new L_block;
            break;
        case 2:
            bl = new Reverse_L_block;
            break;
        case 3:
            bl = new S_block;
            break;
        case 4:
            bl = new Reverse_S_block;
            break;
        case 5:
            bl = new T_block;
            break;
        case 6:
            bl = new Box_block;
            break;
    }
    return bl;
}
