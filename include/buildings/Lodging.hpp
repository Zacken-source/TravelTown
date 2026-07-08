#pragma once
#include "buildings/Building.hpp"

class Lodging : public Building
{
public:
    Lodging(std::string name, int buildCost, int upkeepCost, int capacity)
        : Building(std::move(name), buildCost, upkeepCost), capacity_(capacity) {}

    int         getAttractiveness() const override { return capacity_ / 2; }
    std::string getCategory()       const override { return "Lodging"; }
    std::string getDescription()    const override
    {
        return name_ + " - " + std::to_string(capacity_) + " places";
    }

    int getCapacity() const { return capacity_; }

private:
    int capacity_;
};