#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "ui/Button.hpp"
#include "core/BuildingCatalog.hpp"

class BuildMenu
{
public:
    BuildMenu(const sf::Font& font, const BuildingCatalog& catalog,
              float startX, float startY)
        : font_(font), selectedIndex_(-1)
    {
        const float H = 42.f, W = 220.f, PAD = 4.f;
        for (int i = 0; i < static_cast<int>(catalog.getAll().size()); ++i)
        {
            const auto& info = catalog.getAll()[i];
            buttons_.emplace_back(
                sf::Vector2f(startX, startY + i * (H + PAD)),
                sf::Vector2f(W, H),
                info.name + " (" + std::to_string(info.cost) + "EU)",
                font_
            );
            buildingNames_.push_back(info.name);
        }
    }

    std::string handleClick(sf::Vector2i mp)
    {
        for (int i = 0; i < static_cast<int>(buttons_.size()); ++i)
            if (buttons_[i].contains(mp))
            {
                selectedIndex_ = i;
                for (int j = 0; j < static_cast<int>(buttons_.size()); ++j)
                    buttons_[j].setSelected(j == i);
                return buildingNames_[i];
            }
        return "";
    }

    void handleMouseMove(sf::Vector2i mp)
    {
        for (auto& b : buttons_) b.setHovered(b.contains(mp));
    }

    void render(sf::RenderWindow& w) const
    {
        for (const auto& b : buttons_) b.render(w);
    }

private:
    const sf::Font&          font_;
    std::vector<Button>      buttons_;
    std::vector<std::string> buildingNames_;
    int                      selectedIndex_;
};