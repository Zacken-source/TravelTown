// include/core/BuildingCatalog.hpp
// Charge le catalogue depuis JSON et fournit une factory pour creer les batiments.

#pragma once
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include "buildings/Building.hpp"
#include "buildings/Lodging.hpp"
#include "buildings/SportFacility.hpp"
#include "buildings/Transport.hpp"

struct BuildingInfo
{
    std::string name, type, subtype;
    int cost=0, upkeep=0, capacity=0, prestige=0, flow=0;
};

class BuildingCatalog
{
public:
    void loadFromFile(const std::string& path)
    {
        std::ifstream file(path);
        if (!file.is_open()) throw std::runtime_error("Impossible d'ouvrir: " + path);

        nlohmann::json j;
        file >> j;
        catalog_.clear();

        for (const auto& item : j)
        {
            BuildingInfo info;
            info.name   = item["name"];
            info.type   = item["type"];
            info.cost   = item["cost"];
            info.upkeep = item["upkeep"];
            if (item.contains("capacity"))     info.capacity = item["capacity"];
            if (item.contains("prestige"))     info.prestige = item["prestige"];
            if (item.contains("flow"))         info.flow     = item["flow"];
            if (item.contains("sportType"))    info.subtype  = item["sportType"];
            if (item.contains("transportType"))info.subtype  = item["transportType"];
            catalog_.push_back(info);
        }
    }

    const std::vector<BuildingInfo>& getAll() const { return catalog_; }

       std::shared_ptr<Building> createBuilding(const std::string& name) const
    {
        for (const auto& info : catalog_)
        {
            if (info.name != name) continue;
            if (info.type == "Lodging")
                return std::make_shared<Lodging>(info.name, info.cost, info.upkeep, info.capacity);
            if (info.type == "Sport")
                return std::make_shared<SportFacility>(info.name, info.cost, info.upkeep, info.prestige, info.subtype);
            if (info.type == "Transport")
                return std::make_shared<Transport>(info.name, info.cost, info.upkeep, info.flow, info.subtype);
        }
        return nullptr;
    }

private:
    std::vector<BuildingInfo> catalog_;
};