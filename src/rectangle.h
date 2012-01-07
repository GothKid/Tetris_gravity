#ifndef BUILDING_H
#define BUILDING_H
#include "structure.h"

class Rectangle : Structure {
    public:
        Rectangle(int x, int y, int height, int width);
        bool occupied_at(int x, int y) const;
        void draw() const;
    private:
        int _height;
        int _width;
};
#endif
