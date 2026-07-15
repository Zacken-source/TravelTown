#pragma once
#include "economy/Treasury.hpp"

class TaxSystem
{
public:
    explicit TaxSystem(int taxPerCitizen = 5, float tourismMult = 1.0f)
        : taxPerCitizen_(taxPerCitizen), tourismMult_(tourismMult) {}

    void collectTaxes(int citizenCount, Treasury& treasury)
    {
        int tax = static_cast<int>(citizenCount * taxPerCitizen_ * tourismMult_);
        if (tax > 0) treasury.earn(tax, "Taxes et revenus touristiques");
    }

    void setTourismMultiplier(float m) { tourismMult_ = m; }

private:
    int   taxPerCitizen_;
    float tourismMult_;
};