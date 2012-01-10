#ifndef GAME_H
#define GAME_H
#include <list>
#include "block.h"

void ini_blocks();

void clean_rows(std::list<Block*> blocks);

void delete_empty_blocks(std::list<Block*> blocks);

void advance_blocks(std::list<Block*> blocks);

Block *new_block();

#endif
