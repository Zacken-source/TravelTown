#pragma once
#include <SFML/Graphics.hpp>

class InputHandler
{
public:
    explicit InputHandler(int tileSize) : tileSize_(tileSize) {}

    // Pixel (85,42) avec tileSize=40 -> case (2,1)
    sf::Vector2i screenToGrid(sf::Vector2i mousePos) const
    {
        return { mousePos.x / tileSize_, mousePos.y / tileSize_ };
    }

private:
    int tileSize_;
};