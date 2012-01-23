#include "structure.h"

std::list<Structure*> Structure::structures;
Structure::Structure() : color(GREY) {
    structures.push_back(this);
}

Structure::~Structure() {
    for (std::list<Structure*>::iterator iter = structures.begin(); iter != structures.end(); ++iter) {
        if ((*iter) == this) {
//            delete *iter;
            structures.erase(iter);
            break;
        }
    }
}
