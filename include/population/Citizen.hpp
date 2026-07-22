#pragma once

class Citizen
{
public:
    explicit Citizen(int id) : id_(id), satisfaction_(50) {}

    void updateSatisfaction(int housingQuality, int sportAccess)
    {
        satisfaction_ = (housingQuality * 6 + sportAccess * 4) / 10;
        if (satisfaction_ < 0)   satisfaction_ = 0;
        if (satisfaction_ > 100) satisfaction_ = 100;
    }

    int getId()           const { return id_; }
    int getSatisfaction() const { return satisfaction_; }

private:
    int id_;
    int satisfaction_;
};