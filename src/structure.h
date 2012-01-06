#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <list>
class Structure {
    public:
        Structure(const std::list<Structure*> &);
        bool occupied_at(int x, int y) const;
    protected:
        const std::list<Structure*> &structures;
};
#endif
