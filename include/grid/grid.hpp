#ifndef GRID_H
#define GRID_H

#include <raylib.h>

namespace grid
{
    using numType = unsigned short int;

    class Grid
    {
    private:
        numType gridSize;

    public:
        Grid();
    };
}

#endif