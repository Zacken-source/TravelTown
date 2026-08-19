#pragma once
#include "population/Citizen.hpp"
#include <vector>
#include <algorithm>

class CitizenSorter
{
public:
    static std::vector<Citizen> sortByAscSatisfaction(std::vector<Citizen> citizens)
    {
        std::sort(citizens.begin(), citizens.end(),
            [](const Citizen& a, const Citizen& b){
                return a.getSatisfaction() < b.getSatisfaction();
            });
        return citizens;
    }

    static std::vector<Citizen> getMostUnhappy(
        const std::vector<Citizen>& citizens, int n)
    {
        auto sorted = sortByAscSatisfaction(citizens);
        int count = std::min(n, static_cast<int>(sorted.size()));
        return std::vector<Citizen>(sorted.begin(), sorted.begin() + count);
    }
};