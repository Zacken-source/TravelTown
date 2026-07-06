#include <SFML/Graphics.hpp>
#include "core/Grid.hpp"
#include "ui/GridRenderer.hpp"
#include "core/InputHandler.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1280u, 800u}), "TravelTown");
    window.setFramerateLimit(60);
    InputHandler input(40);
    Grid grid(30, 20);
    grid.at(5, 5) = Tile(TerrainType::Water);
    grid.at(6, 5) = Tile(TerrainType::Water);
    grid.at(7, 5) = Tile(TerrainType::Water);

    grid.at(10, 8) = Tile(TerrainType::Mountain);
    grid.at(11, 8) = Tile(TerrainType::Mountain);
    grid.at(12, 8) = Tile(TerrainType::Mountain);
    GridRenderer renderer(40);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (click->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2i gridPos = input.screenToGrid(click->position);
                    if (grid.isValid(gridPos.x, gridPos.y))
                    {
                        std::cout << "Case (" << gridPos.x << "," << gridPos.y << ")\n";
                    }
                }
            }
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color(235, 224, 200));

        renderer.render(window, grid);

        window.display();
    }

    return 0;
}