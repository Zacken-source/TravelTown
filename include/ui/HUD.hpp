#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "economy/Treasury.hpp"
#include "economy/RessourceManager.hpp"

class HUD
{
public:
    HUD(const sf::Font& font, unsigned int screenWidth)
        : font_(font),
          mainText_(font)
    {
        background_.setSize(sf::Vector2f(static_cast<float>(screenWidth), 50.f));
        background_.setFillColor(sf::Color(30, 40, 60, 220));

        mainText_.setCharacterSize(16);
        mainText_.setFillColor(sf::Color(230, 220, 180));
        mainText_.setPosition({10.f, 14.f});
    }

    void update(int balance, int day, int population,
                const ResourceManager& resources)
    {
        std::string text =
            "Argent: " + std::to_string(balance) + " EU"
            + " | Jour: " + std::to_string(day)
            + " | Habitants: " + std::to_string(population)
            + " | Energie: " + std::to_string(resources.get("energy"))
            + " | Equip: " + std::to_string(resources.get("equipment"));

        mainText_.setString(text);
    }

    void render(sf::RenderWindow& window) const
    {
        window.draw(background_);
        window.draw(mainText_);
    }

private:
    const sf::Font& font_;
    sf::RectangleShape background_;
    sf::Text mainText_;
};