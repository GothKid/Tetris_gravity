#ifndef GAME_H
#define GAME_H
#include <list>
#include "block.h"
#include "rectangle.h"

void ini_blocks(std::list<Rectangle*> &rectangles);

void clean_rows(std::list<Block*> &blocks);

void delete_empty_blocks(std::list<Block*> &blocks);

void advance_blocks(std::list<Block*> &blocks);

void draw_blocks(std::list<Block*> &blocks, Draw_func draw_func);
void draw_rectangles(std::list<Rectangle*> &rectangles, Draw_func draw_func);

Block *new_block();

#endif
