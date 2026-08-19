#pragma once
#include <string>
#include <vector>
#include <random>
#include <functional>

struct GameEvent
{
    std::string name, description;
    int         balanceEffect;
    float       tourismMultiplier;
    int         durationDays;
};

class EventSystem
{
public:
    EventSystem()
        : rng_(std::random_device{}()), dist100_(0, 100)
    {
        events_ = {
            {"Jeux Olympiques Regionaux",
             "Un evenement sportif attire des milliers de visiteurs !",
             5000, 2.0f, 7},
            {"Greve des transports",
             "Moins de visiteurs arrivent en ville.",
             -1000, 0.5f, 3},
            {"Festival extreme",
             "Un festival de sport extreme booste l'attractivite.",
             2000, 1.5f, 5},
            {"Tempete de neige",
             "Les pistes de ski sont fermees.",
             -800, 0.7f, 2},
            {"Championnat de cyclisme",
             "Le velodrome accueille un championnat national !",
             3000, 1.8f, 4}
        };
    }

    const GameEvent* tryTriggerEvent()
    {
        if (dist100_(rng_) < 10)
        {
            std::uniform_int_distribution<int> pick(0, static_cast<int>(events_.size())-1);
            return &events_[pick(rng_)];
        }
        return nullptr;
    }

private:
    std::vector<GameEvent>             events_;
    std::mt19937                       rng_;
    std::uniform_int_distribution<int> dist100_;
};