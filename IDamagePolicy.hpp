#pragma once

#include <cstdint>
#include <string>

class IDamagePolicy
{
public:
    virtual ~IDamagePolicy() = default;

    [[nodiscard]] virtual std::int32_t Reduce(std::int32_t damage) const = 0;
    [[nodiscard]] virtual std::string GetName() const = 0;
};