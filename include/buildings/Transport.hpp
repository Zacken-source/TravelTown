#pragma once
#include "buildings/Building.hpp"

class Transport : public Building
{
public:
    Transport(std::string name, int buildCost, int upkeepCost,
              int visitorFlow, std::string transportType)
        : Building(std::move(name), buildCost, upkeepCost),
          visitorFlow_(visitorFlow), transportType_(std::move(transportType)) {}

    int         getAttractiveness() const override { return visitorFlow_ / 3; }
    std::string getCategory()       const override { return "Transport"; }
    std::string getDescription()    const override
    { return name_ + " (" + transportType_ + ") flux:" + std::to_string(visitorFlow_); }

    int                getVisitorFlow()   const { return visitorFlow_; }
    const std::string& getTransportType() const { return transportType_; }

private:
    int         visitorFlow_;
    std::string transportType_;
};