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
        int x() const;
        int y() const;
        virtual int min_x() const = 0;
        virtual int max_x() const = 0;
        virtual int min_y() const = 0;
        virtual int max_y() const = 0;
    protected:
        static std::list<Structure*> structures;
        int _x;
        int _y;
};
#endif
