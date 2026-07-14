#pragma once
#include "core/Grid.hpp"
#include "economy/Treasury.hpp"
#include "buildings/Building.hpp"

class UpkeepSystem
{
public:
    int calculateTotalUpkeep(const Grid& grid) const
    {
        int total = 0;
        for (int y = 0; y < grid.getHeight(); ++y)
            for (int x = 0; x < grid.getWidth(); ++x)
                if (grid.at(x, y).isOccupied())
                    total += grid.at(x, y).getBuilding()->getUpkeepCost();
        return total;
    }

    bool collectUpkeep(const Grid& grid, Treasury& treasury)
    {
        int cost = calculateTotalUpkeep(grid);
        if (cost == 0) return true;
        return treasury.spend(cost, "Entretien des batiments");
    }
};