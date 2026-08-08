#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "core/Grid.hpp"
#include "buildings/Building.hpp"
#include "buildings/Lodging.hpp"
#include "buildings/SportFacility.hpp"
#include "buildings/Transport.hpp"

class GridRenderer
{
public:
    GridRenderer(int tileSize, const sf::Font& font)
        : tileSize_(tileSize), font_(font)
    {
    }

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

                // Terrain
                switch (tile.getTerrain())
                {
                    case TerrainType::Grass:
                        rect.setFillColor(sf::Color(150, 200, 120));
                        break;

                    case TerrainType::Mountain:
                        rect.setFillColor(sf::Color(160, 150, 140));
                        break;

                    case TerrainType::Water:
                        rect.setFillColor(sf::Color(110, 170, 220));
                        break;
                }


                // Case occupée = assombrissement
                if (tile.isOccupied())
                {
                    sf::Color c = rect.getFillColor();

                    rect.setFillColor(sf::Color(
                        static_cast<std::uint8_t>(c.r * 0.6f),
                        static_cast<std::uint8_t>(c.g * 0.6f),
                        static_cast<std::uint8_t>(c.b * 0.6f)
                    ));
                }


                // Dessin du terrain
                window.draw(rect);


                // Lettre du bâtiment
                if (tile.isOccupied())
                {
                    char letter = '?';

                    std::shared_ptr<Building> building = tile.getBuilding();

                    if (dynamic_cast<Lodging*>(building.get()))
                    {
                        letter = 'H';
                    }
                    else if (dynamic_cast<SportFacility*>(building.get()))
                    {
                        letter = 'S';
                    }
                    else if (dynamic_cast<Transport*>(building.get()))
                    {
                        letter = 'T';
                    }


                    sf::Text text(
                        font_,
                        std::string(1, letter),
                        static_cast<unsigned int>(tileSize_ * 0.6f)
                    );

                    text.setFillColor(sf::Color::White);


                    // Centrage du texte (SFML 3)
                    sf::FloatRect bounds = text.getLocalBounds();

                    text.setOrigin(sf::Vector2f(
                        bounds.position.x + bounds.size.x / 2.f,
                        bounds.position.y + bounds.size.y / 2.f
                    ));


                    text.setPosition(sf::Vector2f(
                        x * tileSize_ + tileSize_ / 2.f,
                        y * tileSize_ + tileSize_ / 2.f
                    ));


                    window.draw(text);
                }
            }
        }
    }


    int getTileSize() const
    {
        return tileSize_;
    }


private:
    int tileSize_;
    const sf::Font& font_;
};
