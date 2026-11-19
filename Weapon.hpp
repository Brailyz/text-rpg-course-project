#pragma once

#include "BaseItem.hpp"
#include "ISellable.hpp"
#include "ItemEffect.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

class Weapon : public BaseItem, public ISellable
{
private:
    static constexpr std::int32_t PRICE_PER_DAMAGE{ 10 };

    std::int32_t m_damage;
    std::unique_ptr<ItemEffect> m_effect;
    bool m_sold{ false };

    [[nodiscard]] static std::unique_ptr<ItemEffect> CopyEffect(const ItemEffect* source);

public:
    Weapon();
    Weapon(const std::string& name, const std::string& description,
        std::int32_t damage, const ItemEffect& effect);
    Weapon(const Weapon& other);
    Weapon(Weapon&& other) noexcept;
    ~Weapon() noexcept override;

    Weapon& operator=(const Weapon& other);
    Weapon& operator=(Weapon&& other) noexcept;

    void Use() const override;
    void Describe() const override;
    [[nodiscard]] std::unique_ptr<BaseItem> Clone() const override;
    [[nodiscard]] std::string GetTypeName() const override;

    [[nodiscard]] std::string GetCategory() const
    {
        return "weapon";
    }

    // ISellable
    [[nodiscard]] std::int32_t GetPrice() const override;
    [[nodiscard]] bool IsSold() const override;
    void Sell(std::string_view buyer) override;

    void SetEffectPower(std::int32_t power);
    [[nodiscard]] std::int32_t GetEffectPower() const;
};
