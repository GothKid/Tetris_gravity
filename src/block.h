#ifndef BLOCK_H
#define BLOCK_H
const int SHAPE_SIDE = 4;

typedef enum {Left, Right, Down} Collision

class Block {
public:
    Block();
    Collision collides(const &block);
private:
    bool shape[SHAPE_SIDE*SHAPE_SIDE];
protected:
    int _x;
    int _y;
}

#endif
