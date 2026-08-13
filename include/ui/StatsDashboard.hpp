#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>

class StatsDashboard
{
public:
    StatsDashboard(const sf::Font& font, sf::Vector2f pos, sf::Vector2f size)
        : font_(font), pos_(pos), size_(size)
    {
        bg_.setPosition(pos);
        bg_.setSize(size);
        bg_.setFillColor(sf::Color(20, 30, 50, 200));
        bg_.setOutlineColor(sf::Color(100, 130, 170));
        bg_.setOutlineThickness(1.f);
    }

    void recordDay(int population, int balance)
    {
        popHist_.push_back(population);
        balHist_.push_back(balance);
        if (popHist_.size() > 30) popHist_.erase(popHist_.begin());
        if (balHist_.size() > 30) balHist_.erase(balHist_.begin());
    }

    void render(sf::RenderWindow& window) const
    {
        window.draw(bg_);
        if (popHist_.empty()) return;

        sf::Text title(font_, "Stats (30j)", 13);
        title.setFillColor(sf::Color(200, 190, 150));
        title.setPosition({pos_.x + 5.f, pos_.y + 5.f});
        window.draw(title);

        int   mx   = *std::max_element(popHist_.begin(), popHist_.end());
        float bW   = (size_.x - 10.f) / 30.f;
        float maxH = size_.y / 2.f - 25.f;
        float baseY = pos_.y + size_.y / 2.f;

        for (int i = 0; i < static_cast<int>(popHist_.size()); ++i)
        {
            float h = (mx > 0) ? (static_cast<float>(popHist_[i]) / mx) * maxH : 0.f;
            sf::RectangleShape bar({bW - 1.f, h});
            bar.setFillColor(sf::Color(80, 160, 220));
            bar.setPosition({pos_.x + 5.f + i * bW, baseY - h});
            window.draw(bar);
        }
    }

private:
    const sf::Font&    font_;
    sf::Vector2f       pos_, size_;
    sf::RectangleShape bg_;
    std::vector<int>   popHist_, balHist_;
};