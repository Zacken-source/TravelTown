#pragma once
#include <memory>

class Building;

enum class TerrainType { Grass, Mountain, Water };

class Tile {
public:
    Tile(TerrainType terrain = TerrainType::Grass) : terrain_(terrain) {}

    bool isOccupied() const { return building_ != nullptr; }
    void setBuilding(std::shared_ptr<Building> b) { building_ = b; }
    std::shared_ptr<Building> getBuilding() const { return building_; }
    TerrainType getTerrain() const { return terrain_; }

    int attractiveness = 0;

private:
    TerrainType terrain_;
    std::shared_ptr<Building> building_ = nullptr;
};