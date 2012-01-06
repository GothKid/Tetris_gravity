#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <list>
class Structure {
    public:
        Structure();
        virtual bool occupied_at(int x, int y) const = 0;
    protected:
        static std::list<Structure*> structures;
};
#endif
