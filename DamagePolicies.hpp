#pragma once

#include "IDamagePolicy.hpp"

#include <algorithm>

class NoProtection : public IDamagePolicy
{
public:
    [[nodiscard]] std::int32_t Reduce(std::int32_t damage) const override
    {
        return damage;
    }

    [[nodiscard]] std::string GetName() const override
    {
        return "no protection";
    }
};

class LightArmor : public IDamagePolicy
{
private:
    static constexpr std::int32_t REDUCTION{ 5 };

public:
    [[nodiscard]] std::int32_t Reduce(std::int32_t damage) const override
    {
        return std::max(0, damage - REDUCTION);
    }

    [[nodiscard]] std::string GetName() const override
    {
        return "light armor";
    }
};

class HeavyArmor : public IDamagePolicy
{
public:
    [[nodiscard]] std::int32_t Reduce(std::int32_t damage) const override
    {
        return damage / 2;
    }

    [[nodiscard]] std::string GetName() const override
    {
        return "heavy armor";
    }
};