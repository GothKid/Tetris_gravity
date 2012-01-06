#ifndef BLOCK_H
#define BLOCK_H
#include "structure.h"
const int SHAPE_SIDE = 4;

class Block : public Structure {
    public:
        /**
         * @brief Construct a block
         * @param Reference to a list that contains all structures
         */
        Block();
        void move_left();
        void move_right();
        void move_up();
        void move_down();
        void rotate();
    protected:
        /**
         * @brief Check if a structure collides with this block
         * @param Reference to the other structure
         */
        bool collides(const Structure&) const;
        /**
         * @brief Check if this block occupies the given coordinates
         * @param X coordinate
         * @param Y coordinate
         * @return true if there is a collision, false otherwise
         */
        bool occupied_at(int x, int y) const;
        /**
         * @brief Check if this block collides with any of the other
         * structures
         * @return true if there is a collision, false otherwise
         */
        bool check_collides() const;
        /**
         * @brief Stores if a cell is occupied by this block
         */
        bool shape[SHAPE_SIDE*SHAPE_SIDE];
        int _x;
        int _y;
        int _rotation;
        virtual const bool (*get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE] = 0;
};

class Line_block : public Block {
    public:
        Line_block();
    private:
        const bool (*get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE];
        const static bool _rotation_data[4][SHAPE_SIDE*SHAPE_SIDE];
};

#endif
