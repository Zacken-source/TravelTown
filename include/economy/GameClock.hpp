#pragma once
#include <functional>

class GameClock
{
public:
    explicit GameClock(float dayDuration = 10.f)
        : dayDuration_(dayDuration), elapsed_(0.f), dayCount_(0) {}

    void update(float deltaSeconds)
    {
        elapsed_ += deltaSeconds;
        if (elapsed_ >= dayDuration_)
        {
            elapsed_ -= dayDuration_;
            ++dayCount_;
            if (onNewDay) onNewDay(dayCount_);
        }
    }

    int   getDayCount() const { return dayCount_; }
    float getProgress() const { return elapsed_ / dayDuration_; }

    // Callback appele quand un jour passe
    // Exemple : clock.onNewDay = [&](int day){ upkeep.collect(grid, treasury); };
    std::function<void(int)> onNewDay;

private:
    float dayDuration_, elapsed_;
    int   dayCount_;
};