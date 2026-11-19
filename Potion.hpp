#pragma once

#include "BaseItem.hpp"
#include "ISellable.hpp"
#include "ItemEffect.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

class Potion final : public BaseItem, public ISellable
{
private:
    static constexpr std::int32_t PRICE_PER_HEAL{ 2 };

    std::int32_t m_healAmount;
    std::shared_ptr<ItemEffect> m_effect;
    bool m_sold{ false };

public:
    Potion();
    Potion(const std::string& name, const std::string& description,
        std::int32_t healAmount, const ItemEffect& effect);
    ~Potion() noexcept override;

    Potion(const Potion& other) = default;
    Potion(Potion&& other) noexcept = default;
    Potion& operator=(const Potion& other) = default;
    Potion& operator=(Potion&& other) noexcept = default;

    void Use() const override;
    void Describe() const override;
    [[nodiscard]] std::unique_ptr<BaseItem> Clone() const override;
    [[nodiscard]] std::string GetTypeName() const override;

    // ISellable
    [[nodiscard]] std::int32_t GetPrice() const override;
    [[nodiscard]] bool IsSold() const override;
    void Sell(std::string_view buyer) override;

    void SetEffectPower(std::int32_t power);
    [[nodiscard]] long GetEffectUseCount() const;
};