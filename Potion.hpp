#pragma once

#include "BaseItem.hpp"
#include "ItemEffect.hpp"

#include <cstdint>
#include <memory>
#include <string>

class Potion final : public BaseItem
{
private:
    std::int32_t m_healAmount;
    std::shared_ptr<ItemEffect> m_effect;

public:
    Potion();
    Potion(const std::string& name, const std::string& description,
        std::int32_t healAmount, const ItemEffect& effect);
    ~Potion() override;

    Potion(const Potion& other) = default;
    Potion(Potion&& other) = default;
    Potion& operator=(const Potion& other) = default;
    Potion& operator=(Potion&& other) = default;

    void Use() const override;
    void Describe() const override;
    [[nodiscard]] std::unique_ptr<BaseItem> Clone() const override;
    [[nodiscard]] std::string GetTypeName() const override;

    void SetEffectPower(std::int32_t power);
    [[nodiscard]] long GetEffectUseCount() const;
};
