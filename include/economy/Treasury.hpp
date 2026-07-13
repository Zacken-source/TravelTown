#pragma once
#include <string>
#include <vector>

struct Transaction { int amount; std::string description; };

class Treasury
{
public:
    explicit Treasury(int startingBalance = 10000) : balance_(startingBalance) {}

    bool canAfford(int amount) const { return balance_ >= amount; }

    bool spend(int amount, const std::string& desc = "Depense")
    {
        if (!canAfford(amount)) return false;
        balance_ -= amount;
        history_.push_back({-amount, desc});
        return true;
    }

    void earn(int amount, const std::string& desc = "Revenu")
    {
        balance_ += amount;
        history_.push_back({amount, desc});
    }

    int                             getBalance() const { return balance_; }
    const std::vector<Transaction>& getHistory() const { return history_; }

private:
    int                      balance_;
    std::vector<Transaction> history_;
};