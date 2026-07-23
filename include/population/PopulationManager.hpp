#pragma once
#include "population/Citizen.hpp"
#include "core/Grid.hpp"
#include "buildings/Lodging.hpp"
#include <vector>
#include <numeric>

class PopulationManager
{
public:

    int calculateTotalCapacity(const Grid& grid) const
    {
        int cap = 0;
        for (int y = 0; y < grid.getHeight(); ++y)
            for (int x = 0; x < grid.getWidth(); ++x)
                if (grid.at(x, y).isOccupied())
                {

                    auto* l = dynamic_cast<Lodging*>(grid.at(x, y).getBuilding().get());
                    if (l) cap += l->getCapacity();
                }
        return cap;
    }

    int getAverageSatisfaction() const
    {
        if (citizens_.empty()) return 0;
        int total = std::accumulate(citizens_.begin(), citizens_.end(), 0,
            [](int s, const Citizen& c){ return s + c.getSatisfaction(); });
        return total / static_cast<int>(citizens_.size());
    }

    void update(const Grid& grid, int housingQ, int sportA)
    {
        int cap    = calculateTotalCapacity(grid);
        int avgSat = getAverageSatisfaction();

        for (auto& c : citizens_)
            c.updateSatisfaction(housingQ, sportA);

        if (static_cast<int>(citizens_.size()) < cap && avgSat >= 40)
            citizens_.emplace_back(nextId_++);

        if (avgSat < 20 && !citizens_.empty())
            citizens_.pop_back();
    }

    int                         size()        const { return static_cast<int>(citizens_.size()); }
    const std::vector<Citizen>& getCitizens() const { return citizens_; }

private:
    std::vector<Citizen> citizens_;
    int                  nextId_ = 0;
};