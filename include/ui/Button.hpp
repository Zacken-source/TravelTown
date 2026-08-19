#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
    Button(sf::Vector2f pos,
           sf::Vector2f size,
           const std::string& label,
           const sf::Font& font)
        : text_(font, label, 14)
    {
        shape_.setPosition(pos);
        shape_.setSize(size);
        shape_.setFillColor(sf::Color(50, 80, 120));
        shape_.setOutlineColor(sf::Color(200, 180, 120));
        shape_.setOutlineThickness(1.f);

        text_.setFillColor(sf::Color(230, 220, 180));

        sf::FloatRect tb = text_.getLocalBounds();
        text_.setPosition({
            pos.x + (size.x - tb.size.x) / 2.f - tb.position.x,
            pos.y + (size.y - tb.size.y) / 2.f - tb.position.y
        });
    }

    bool contains(sf::Vector2i mp) const
    {
        return shape_.getGlobalBounds().contains(
            sf::Vector2f(static_cast<float>(mp.x),
                         static_cast<float>(mp.y)));
    }

    void setHovered(bool h)
    {
        shape_.setFillColor(h ? sf::Color(80, 120, 180)
                              : sf::Color(50, 80, 120));
    }

    void setSelected(bool s)
    {
        shape_.setOutlineColor(s ? sf::Color(255, 200, 0)
                                 : sf::Color(200, 180, 120));
        shape_.setOutlineThickness(s ? 2.f : 1.f);
    }

    void render(sf::RenderWindow& window) const
    {
        window.draw(shape_);
        window.draw(text_);
    }

private:
    sf::RectangleShape shape_;
    sf::Text text_;
};