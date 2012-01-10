#include "../game.h"

int main() {
    ini_blocks();
    std::list<Block*> blocks;
    Block *bl1 = new Line_block;
    blocks.push_back(bl1);
    if (!bl1) {
        fprintf(stderr, "Error creando bloque nuevo\n");
        return 1;
    }
    bl1->draw();
    printf("\n");
    bl1->rotate();
    bl1->draw();
    printf("\n");
    for (int i = 0; i < 30; i++)
        advance_blocks(blocks);
    bl1->draw();
    printf("\n");

    Block *bl2 = new Line_block;
    if (!bl2) {
        fprintf(stderr, "Error creando bloque nuevo\n");
        return 1;
    }
    blocks.push_back(bl2);
    bl2->draw();
    printf("\n");
    bl2->rotate();
    bl2->move_right();
    bl2->move_right();
    bl2->move_right();
    bl2->move_right();
    bl2->draw();
    printf("\n");
    for (int i = 0; i < 30; i++)
        advance_blocks(blocks);
    bl2->draw();
    printf("\n");

    clean_rows(blocks);
    bl2->draw();

    delete_empty_blocks(blocks);

    return 0;
}
