#pragma once
#include <string>

class Building
{
public:
    Building(std::string name, int buildCost, int upkeepCost)
        : name_(std::move(name)), buildCost_(buildCost), upkeepCost_(upkeepCost) {}

    virtual ~Building() = default;

    virtual int         getAttractiveness() const = 0;
    virtual std::string getCategory()       const = 0;
    virtual std::string getDescription()    const = 0;

    const std::string& getName()       const { return name_; }
    int                getBuildCost()  const { return buildCost_; }
    int                getUpkeepCost() const { return upkeepCost_; }

protected:
    std::string name_;
    int         buildCost_;
    int         upkeepCost_;
};