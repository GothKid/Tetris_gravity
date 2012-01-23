#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <list>
#include "draw.h"


class Structure {
    public:
        Structure();
        ~Structure();
        virtual bool occupied_at(int x, int y) const = 0;
        virtual void draw(Draw_func) const = 0;
        const COLOR color;
    protected:
        static std::list<Structure*> structures;
        int _x;
        int _y;
};
#endif
