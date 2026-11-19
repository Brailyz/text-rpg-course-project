#pragma once

#include "BaseItem.hpp"
#include "Inventory.hpp"

#include <cstdint>
#include <memory>
#include <string>

class Character
{
private:
    std::string m_name;

    std::int32_t m_health;
    std::int32_t m_maxHealth;

    Inventory m_inventory;

    std::weak_ptr<BaseItem> m_lastUsedItem;

public:
    Character(const std::string& name, std::int32_t health, std::int32_t maxHealth);
    ~Character();

    Character(const Character&) = delete;
    Character(Character&&) = delete;
    Character& operator=(const Character&) = delete;
    Character& operator=(Character&&) = delete;

    [[nodiscard]] const std::string& GetName() const;
    [[nodiscard]] std::int32_t GetHealth() const;
    [[nodiscard]] std::int32_t GetMaxHealth() const;

    void TakeDamage(std::int32_t damage);
    void AddItem(const std::shared_ptr<BaseItem>& item);
    void RemoveItem(const BaseItem* item);
    void UseItem(const std::shared_ptr<BaseItem>& item);
    void ShowLastUsedItem() const;
    void ShowInventory() const;
    void ShowInfo() const;
};
