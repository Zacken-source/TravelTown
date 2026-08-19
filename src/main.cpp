// src/main.cpp - version finale integrant tous les systemes

#include <SFML/Graphics.hpp>
#include <iostream>
#include "core/Grid.hpp"
#include "core/InputHandler.hpp"
#include "core/BuildingCatalog.hpp"
#include "core/AttractivenessSystem.hpp"
#include "ui/GridRenderer.hpp"
#include "ui/HUD.hpp"
#include "ui/BuildMenu.hpp"
#include "ui/Button.hpp"
#include "economy/Treasury.hpp"
#include "economy/RessourceManager.hpp"
#include "economy/GameClock.hpp"
#include "economy/UpkeepSystem.hpp"
#include "economy/TaxSystem.hpp"
#include "population/PopulationManager.hpp"
#include "persistence/SaveManager.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1280u, 800u}), "TravelTown");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.openFromFile("../assets/fonts/DejaVuSans.ttf"))
    { std::cerr << "Police manquante\n"; return -1; }

    const int TILE_SIZE = 38;
    Grid                 grid(28, 18);
    GridRenderer         renderer(TILE_SIZE, font);
    InputHandler         input(TILE_SIZE);
    AttractivenessSystem attrSys;

    BuildingCatalog catalog;
    catalog.loadFromFile("../assets/data/buildings.json");

    Treasury        treasury(10000);
    ResourceManager resources;
    GameClock       clock(10.f);   
    UpkeepSystem    upkeep;
    TaxSystem       taxes;
    PopulationManager population;
    SaveManager     saveManager;

    HUD hud(font, 1280);
    BuildMenu buildMenu(font, catalog, 1042.f, 60.f);
    std::string selectedBuilding;

    Button btnSave({1042.f, 730.f}, {110.f, 35.f}, "Sauvegarder", font);
    Button btnLoad({1162.f, 730.f}, {110.f, 35.f}, "Charger",     font);

    sf::Clock sfClock;

    clock.onNewDay = [&](int)
    {
        upkeep.collectUpkeep(grid, treasury);
        taxes.collectTaxes(population.size(), treasury);
        population.update(grid, 60, 50);
    };

    while (window.isOpen())
    {
        float dt = sfClock.restart().asSeconds();
        clock.update(dt);

        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* m = event->getIf<sf::Event::MouseMoved>())
                buildMenu.handleMouseMove(m->position);

            if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (click->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i mp = click->position;

                    std::string chosen = buildMenu.handleClick(mp);
                    if (!chosen.empty())
                    {
                        selectedBuilding = chosen;
                    }
                    else if (btnSave.contains(mp))
                    {
                        saveManager.save("save.json", grid, treasury,
                                         resources, population, clock.getDayCount());
                        std::cout << "[Sauvegarde OK]\n";
                    }
                    else if (btnLoad.contains(mp))
                    {
                        try {
                            auto r = saveManager.load("save.json", grid, resources, catalog);
                            int diff = r.balance - treasury.getBalance();
                            if (diff > 0) treasury.earn(diff, "Chargement");
                            attrSys.recalculate(grid);
                            std::cout << "[Chargement OK] Jour " << r.dayCount << "\n";
                        } catch (const std::exception& e) {
                            std::cerr << "Erreur: " << e.what() << "\n";
                        }
                    }
                    else if (!selectedBuilding.empty())
                    {
                        sf::Vector2i gp = input.screenToGrid(mp);
                        if (grid.isValid(gp.x, gp.y) && !grid.at(gp.x, gp.y).isOccupied())
                            for (const auto& info : catalog.getAll())
                                if (info.name == selectedBuilding
                                    && treasury.spend(info.cost, "Construction: " + info.name))
                                {
                                    grid.at(gp.x, gp.y).setBuilding(catalog.createBuilding(info.name));
                                    attrSys.recalculate(grid);
                                    break;
                                }
                    }
                }
            }
        }

        hud.update(treasury.getBalance(), clock.getDayCount(),
                   population.size(), resources);

        window.clear(sf::Color(20, 25, 35));
        renderer.render(window, grid);
        hud.render(window);
        buildMenu.render(window);
        btnSave.render(window);
        btnLoad.render(window);
        window.display();
    }
    return 0;
}