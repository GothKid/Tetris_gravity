#ifndef BLOCK_H
#define BLOCK_H
#include "structure.h"
const int SHAPE_SIDE = 4;

class Block : Structure {
    public:
        Block();
        bool collides(const Structure&) const;
        bool occupied_at(int x, int y) const;
    private:
        bool shape[SHAPE_SIDE*SHAPE_SIDE];
        int _x;
        int _y;
};

#endif
