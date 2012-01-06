#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <list>
class Structure {
    public:
        Structure(const std::list<Structure*> &s);
        virtual bool occupied_at(int x, int y) const = 0;
    protected:
        const std::list<Structure*> &structures;
};
#endif
