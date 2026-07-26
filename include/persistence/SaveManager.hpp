#pragma once
#include <string>
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include "core/Grid.hpp"
#include "economy/Treasury.hpp"
#include "economy/RessourceManager.hpp"
#include "population/PopulationManager.hpp"
#include "core/BuildingCatalog.hpp"

class SaveManager
{
public:
    void save(const std::string& filepath,
              const Grid& grid,
              const Treasury& treasury,
              const ResourceManager& resources,
              const PopulationManager& population,
              int dayCount)
    {
        nlohmann::json j;
        j["version"]    = "1.0";
        j["dayCount"]   = dayCount;
        j["balance"]    = treasury.getBalance();
        j["population"] = population.size();

        for (const auto& [name, amount] : resources.getAll())
            j["resources"][name] = amount;

        j["buildings"] = nlohmann::json::array();
        for (int y = 0; y < grid.getHeight(); ++y)
            for (int x = 0; x < grid.getWidth(); ++x)
                if (grid.at(x, y).isOccupied())
                    j["buildings"].push_back({
                        {"x", x}, {"y", y},
                        {"name", grid.at(x, y).getBuilding()->getName()}
                    });

        std::ofstream file(filepath);
        if (!file.is_open()) throw std::runtime_error("Ecriture impossible: " + filepath);
        file << j.dump(4);
    }

    struct LoadResult { int balance, dayCount, population; };

    LoadResult load(const std::string& filepath, Grid& grid,
                    ResourceManager& resources, const BuildingCatalog& catalog)
    {
        std::ifstream file(filepath);
        if (!file.is_open()) throw std::runtime_error("Fichier introuvable: " + filepath);

        nlohmann::json j;
        file >> j;

        LoadResult r;
        r.balance    = j["balance"];
        r.dayCount   = j["dayCount"];
        r.population = j.value("population", 0);

        if (j.contains("resources"))
            for (auto& [name, amount] : j["resources"].items())
            {
                int diff = static_cast<int>(amount) - resources.get(name);
                if (diff > 0) resources.add(name, diff);
            }

        for (const auto& entry : j["buildings"])
        {
            int x = entry["x"], y = entry["y"];
            std::string name = entry["name"];
            if (grid.isValid(x, y))
            {
                auto b = catalog.createBuilding(name);
                if (b) grid.at(x, y).setBuilding(b);
            }
        }

        return r;
    }
};