#pragma once
#include <memory>

class Building;

enum class TerrainType { Grass, Mountain, Water };

class Tile
{
public:
    explicit Tile(TerrainType terrain = TerrainType::Grass)
        : terrain_(terrain), building_(nullptr), attractiveness_(0) {}

    TerrainType getTerrain()   const { return terrain_; }
    bool        isOccupied()   const { return building_ != nullptr; }

    void setBuilding(std::shared_ptr<Building> b) { building_ = std::move(b); }
    void clearBuilding()                           { building_ = nullptr; }

    std::shared_ptr<Building> getBuilding() const { return building_; }

    int  getAttractiveness() const    { return attractiveness_; }
    void setAttractiveness(int v)     { attractiveness_ = v; }
    void addAttractiveness(int v)     { attractiveness_ += v; }

private:
    TerrainType               terrain_;
    std::shared_ptr<Building> building_;
    int                       attractiveness_;
};