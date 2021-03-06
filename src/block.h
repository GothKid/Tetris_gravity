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

#ifndef BLOCK_H
#define BLOCK_H
#include <string.h>
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
        
        /**
         * @brief Check if the point is in the region occupied
         * by the SHAPE_SIDE * SHAPE_SIDE square
         * @param X coordinate
         * @param Y coordinate
         * @return true or false
         */
        bool is_possibly_occupied(int, int) const;
        static Block *moving_block();
        static void reset_moving_block();
        void delete_row(int row);
        void draw(Draw_func) const;
        /**
         * @brief Check if this block occupies the given coordinates
         * @param X coordinate
         * @param Y coordinate
         * @return true if there is a collision, false otherwise
         */
        bool occupied_at(int x, int y) const;
        bool empty() const;
        bool check_collides() const;
    protected:
        /**
         * @brief Check if a structure collides with this block
         * @param Reference to the other structure
         */
        bool collides(const Structure&) const;
        /**
         * @brief Check if this block collides with any of the other
         * structures
         * @return true if there is a collision, false otherwise
         */
        /**
         * @brief Stores if a cell is occupied by this block
         */
        bool shape[SHAPE_SIDE*SHAPE_SIDE];
        int _rotation;
        virtual const bool (*get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE] = 0;
        virtual COLOR getcolor() const = 0;
        static Block *_moving;
        int min_x() const;
        int max_x() const;
        int min_y() const;
        int max_y() const;
};

class Line_block : public Block {
    public:
        Line_block();
    private:
        const bool (*get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE];
        const static bool _rotation_data[4][SHAPE_SIDE*SHAPE_SIDE];
    protected:
        COLOR getcolor() const;
};
class L_block : public Block {
    public:
        L_block();
    private:
        const bool (*get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE];
        const static bool _rotation_data[4][SHAPE_SIDE*SHAPE_SIDE];
    protected:
        COLOR getcolor() const;
};
class Reverse_L_block : public Block {
    public:
        Reverse_L_block();
    private:
        const bool (*get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE];
        const static bool _rotation_data[4][SHAPE_SIDE*SHAPE_SIDE];
    protected:
        COLOR getcolor() const;
};
class Box_block : public Block {
    public:
        Box_block();
    private:
        const bool (*get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE];
        const static bool _rotation_data[4][SHAPE_SIDE*SHAPE_SIDE];
    protected:
        COLOR getcolor() const;
};
class S_block : public Block {
    public:
        S_block();
    private:
        const bool (*get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE];
        const static bool _rotation_data[4][SHAPE_SIDE*SHAPE_SIDE];
    protected:
        COLOR getcolor() const;
};
class Reverse_S_block : public Block {
    public:
        Reverse_S_block();
    private:
        const bool (*get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE];
        const static bool _rotation_data[4][SHAPE_SIDE*SHAPE_SIDE];
    protected:
        COLOR getcolor() const;
};
class T_block : public Block {
    public:
        T_block();
    private:
        const bool (*get_rotation_data())[SHAPE_SIDE*SHAPE_SIDE];
        const static bool _rotation_data[4][SHAPE_SIDE*SHAPE_SIDE];
    protected:
        COLOR getcolor() const;
};

#endif
