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

#ifndef GAME_H
#define GAME_H
#include <list>
#include "block.h"
#include "rectangle.h"

void ini_blocks(std::list<Rectangle*> &rectangles);

int clean_rows(std::list<Block*> &blocks);

void delete_empty_blocks(std::list<Block*> &blocks);

void advance_blocks(std::list<Block*> &blocks);

void draw_blocks(std::list<Block*> &blocks, Draw_func draw_func);
void draw_rectangles(std::list<Rectangle*> &rectangles, Draw_func draw_func);

Block *new_block();

#endif
