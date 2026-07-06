#pragma once
#include <SFML/Graphics.hpp>
#include "core/Grid.hpp"
#include <iostream>
class GridRenderer
{
public:
    explicit GridRenderer(int tileSize) : tileSize_(tileSize) {}

    void render(sf::RenderWindow& window, const Grid& grid) const
    {
        for (int y = 0; y < grid.getHeight(); ++y)
        {
            for (int x = 0; x < grid.getWidth(); ++x)
            {
                sf::RectangleShape rect(sf::Vector2f(
                    static_cast<float>(tileSize_ - 1),
                    static_cast<float>(tileSize_ - 1)
                ));
                rect.setPosition(sf::Vector2f(
                    static_cast<float>(x * tileSize_),
                    static_cast<float>(y * tileSize_)
                ));

                const Tile& tile = grid.at(x, y);
                switch (tile.getTerrain())
                {
                    case TerrainType::Grass:
                        rect.setFillColor(sf::Color(150, 200, 120)); break;
                    case TerrainType::Mountain:
                        rect.setFillColor(sf::Color(160, 150, 140)); break;
                    case TerrainType::Water:
                        rect.setFillColor(sf::Color(110, 170, 220)); break;
                }

                if (tile.isOccupied())
                {
                    sf::Color c = rect.getFillColor();
                    rect.setFillColor(sf::Color(
                        c.r * 0.6f,
                        c.g * 0.6f,
                        c.b * 0.6f
                    ));
                }
                window.draw(rect);
            }
        }
    }

    int getTileSize() const { return tileSize_; }

private:
    int tileSize_;
};