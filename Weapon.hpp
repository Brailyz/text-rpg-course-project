#pragma once

#include "BaseItem.hpp"
#include "ItemEffect.hpp"

#include <cstdint>
#include <memory>
#include <string>

class Weapon : public BaseItem
{
private:
    std::int32_t m_damage;
    std::unique_ptr<ItemEffect> m_effect;

    [[nodiscard]] static std::unique_ptr<ItemEffect> CopyEffect(const ItemEffect* source);

public:
    Weapon();
    Weapon(const std::string& name, const std::string& description,
        std::int32_t damage, const ItemEffect& effect);
    Weapon(const Weapon& other);
    Weapon(Weapon&& other) noexcept;
    ~Weapon() override;

    Weapon& operator=(const Weapon& other);
    Weapon& operator=(Weapon&& other) noexcept;

    void Use() const override;
    void Describe() const override;
    [[nodiscard]] std::unique_ptr<BaseItem> Clone() const override;
    [[nodiscard]] std::string GetTypeName() const override;

    void SetEffectPower(std::int32_t power);
    [[nodiscard]] std::int32_t GetEffectPower() const;
};
