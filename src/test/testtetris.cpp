#include "../game.h"

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
    bl1->draw(TERM);
    printf("\n");
    bl1->rotate();
    bl1->draw(TERM);
    printf("\n");
    for (int i = 0; i < 30; i++)
        advance_blocks(blocks);
    bl1->draw(TERM);
    printf("\n");

    Block *bl2 = new Line_block;
    if (!bl2) {
        fprintf(stderr, "Error creando bloque nuevo\n");
        return 1;
    }
    blocks.push_back(bl2);
    bl2->draw(TERM);
    printf("\n");
    bl2->rotate();
    bl2->move_right();
    bl2->move_right();
    bl2->move_right();
    bl2->move_right();
    bl2->draw(TERM);
    printf("\n");
    for (int i = 0; i < 30; i++)
        advance_blocks(blocks);
    bl2->draw(TERM);
    printf("\n");

    clean_rows(blocks);
    bl2->draw(TERM);

    delete_empty_blocks(blocks);

    return 0;
}
