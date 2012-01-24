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

#include "../game.h"

void console_draw(std::list<Coord>, COLOR);

int main() {
    std::list<Rectangle*> rectangles;
    ini_blocks(rectangles);
    std::list<Block*> blocks;
    Block *bl1 = new Line_block;
    blocks.push_back(bl1);
    if (!bl1) {
        fprintf(stderr, "Error creando bloque nuevo\n");
        return 1;
    }
    bl1->draw(console_draw);
    printf("\n");
    bl1->rotate();
    bl1->draw(console_draw);
    printf("\n");
    for (int i = 0; i < 30; i++)
        advance_blocks(blocks);
    bl1->draw(console_draw);
    printf("\n");

    Block *bl2 = new Line_block;
    if (!bl2) {
        fprintf(stderr, "Error creando bloque nuevo\n");
        return 1;
    }
    blocks.push_back(bl2);
    bl2->draw(console_draw);
    printf("\n");
    bl2->rotate();
    bl2->move_right();
    bl2->move_right();
    bl2->move_right();
    bl2->move_right();
    bl2->draw(console_draw);
    printf("\n");
    for (int i = 0; i < 30; i++)
        advance_blocks(blocks);
    bl2->draw(console_draw);
    printf("\n");

    clean_rows(blocks);
    bl2->draw(console_draw);

    delete_empty_blocks(blocks);

    return 0;
}

void console_draw(std::list<Coord> coords, COLOR c) {
    for (std::list<Coord>::const_iterator i = coords.begin(); i != coords.end(); ++i)
        fprintf(stderr, "Occupied at: %d,%d\n", i->x, i->y);
}
