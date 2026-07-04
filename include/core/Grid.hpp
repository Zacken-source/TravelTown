#pragma once
#include "core/Tile.hpp"
#include <vector>
#include <stdexcept>

class Grid
{
public:
    Grid(int width, int height)
        : width_(width), height_(height),
          tiles_(height, std::vector<Tile>(width))
    {}

    Tile& at(int x, int y)
    {
        if (!isValid(x, y))
            throw std::out_of_range("Grid::at - hors limites");
        return tiles_[y][x];
    }

    // Acces en lecture seule
    const Tile& at(int x, int y) const
    {
        if (!isValid(x, y))
            throw std::out_of_range("Grid::at - hors limites");
        return tiles_[y][x];
    }

    bool isValid(int x, int y) const
    {
        return x >= 0 && x < width_ && y >= 0 && y < height_;
    }

    int getWidth()  const { return width_; }
    int getHeight() const { return height_; }

private:
    int width_, height_;
    std::vector<std::vector<Tile>> tiles_;
};