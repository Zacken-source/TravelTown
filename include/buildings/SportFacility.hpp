#pragma once
#include "buildings/Building.hpp"

class SportFacility : public Building
{
public:
    SportFacility(std::string name, int buildCost, int upkeepCost,
                  int prestige, std::string sportType)
        : Building(std::move(name), buildCost, upkeepCost),
          prestige_(prestige), sportType_(std::move(sportType)) {}

    int         getAttractiveness() const override { return prestige_; }
    std::string getCategory()       const override { return "Sport"; }
    std::string getDescription()    const override
    { return name_ + " (" + sportType_ + ") prestige:" + std::to_string(prestige_); }

    int                getPrestige()  const { return prestige_; }
    const std::string& getSportType() const { return sportType_; }

private:
    int         prestige_;
    std::string sportType_;
};