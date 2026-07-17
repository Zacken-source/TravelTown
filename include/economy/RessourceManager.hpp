#pragma once
#include <unordered_map>
#include <string>

class ResourceManager
{
public:
    ResourceManager()
    {
        stock_["energy"]    = 100;
        stock_["equipment"] = 50;
    }

    void add(const std::string& res, int amount) { stock_[res] += amount; }

    bool consume(const std::string& res, int amount)
    {
        auto it = stock_.find(res);
        if (it == stock_.end() || it->second < amount) return false;
        it->second -= amount;
        return true;
    }
    int get(const std::string& res) const
    {
        auto it = stock_.find(res);
        return (it != stock_.end()) ? it->second : 0;
    }

    const std::unordered_map<std::string, int>& getAll() const { return stock_; }

private:
    std::unordered_map<std::string, int> stock_;
};