#include "structure.h"

std::list<Structure*> Structure::structures;
Structure::Structure() {
    structures.push_back(this);
}
