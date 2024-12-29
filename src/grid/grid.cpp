#include "grid.hpp"

namespace grid
{
    Grid::Grid()
    {
        this->gridSize = 10;
    }

    auto Grid::getGridSize() const -> numType
    {
        return this->gridSize;
    }
}