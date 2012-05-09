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

#include "game.h"
#include "block.h"
#include <cstdlib>
#include <ctime>

typedef std::list<Block*>::iterator block_iter;
typedef std::list<Rectangle*>::iterator rectangle_iter;
const int HEIGHT = 20;
const int WIDTH = 8;
void ini_blocks(std::list<Rectangle*> &rectangles) {
#ifdef __APPLE__
    srandom(time(0));
#else
    srand(time(0));
#endif
    rectangles.push_back(new Rectangle(0, 0, HEIGHT, 1));
    rectangles.push_back(new Rectangle(WIDTH+1, 0, HEIGHT, 1));
    rectangles.push_back(new Rectangle(1, HEIGHT, 1, WIDTH));
} 

int clean_rows(std::list<Block*> &blocks) {
    int deleted = 0;
    for (int i = 0; i <= HEIGHT; ++i) {
        int occupied = 0;
        for (int j = 1; j <= WIDTH; ++j) {
            for (block_iter iter = blocks.begin(); iter != blocks.end(); ++iter) {
                if ((*iter)->occupied_at(j, i)) 
                    ++occupied;
            }
        }
        if (occupied == WIDTH) {
            for (block_iter iter = blocks.begin(); iter != blocks.end(); ++iter)
                (*iter)->delete_row(i);
            ++deleted;
        }
    }
    return deleted;
}

void delete_empty_blocks(std::list<Block*> &blocks) {
    for (block_iter iter = blocks.begin(); iter != blocks.end(); ++iter) {
        if ((*iter)->empty()) {
            delete *iter;
            iter = blocks.erase(iter);
            if (iter == blocks.end())
                break;
        }
    }
}

void advance_blocks(std::list<Block*> &blocks) {
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

void draw_blocks(std::list<Block*> &blocks, Draw_func draw_func) {
    for (block_iter i = blocks.begin(); i != blocks.end(); ++i) {
        (*i)->draw(draw_func);
    }
}
void draw_rectangles(std::list<Rectangle*> &rectangles, Draw_func draw_func) {
    for (rectangle_iter i = rectangles.begin(); i != rectangles.end(); ++i)
        (*i)->draw(draw_func);
}
