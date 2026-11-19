#pragma once

#include <cstdint>
#include <string_view>

class ISellable
{
public:
    virtual ~ISellable() = default;

    [[nodiscard]] virtual std::int32_t GetPrice() const = 0;
    [[nodiscard]] virtual bool IsSold() const = 0;
    virtual void Sell(std::string_view buyer) = 0;
};