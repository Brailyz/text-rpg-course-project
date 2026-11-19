#pragma once

#include "BaseItem.hpp"

#include <cstdint>
#include <memory>

class Character;

class Inventory
{
private:
    const Character& m_owner;
    std::unique_ptr<std::shared_ptr<BaseItem>[]> m_items;
    std::int32_t m_size;
    std::int32_t m_capacity;

    void Resize();

public:
    explicit Inventory(const Character& owner);
    ~Inventory() noexcept;

    Inventory(const Inventory&) = delete;
    Inventory(Inventory&&) = delete;
    Inventory& operator=(const Inventory&) = delete;
    Inventory& operator=(Inventory&&) = delete;

    void AddItem(const std::shared_ptr<BaseItem>& item);

    void RemoveItem(const BaseItem* item);
    void UseItem(const BaseItem* item) const;

    void ShowItems() const;
    [[nodiscard]] bool HasItem(const BaseItem* item) const;
};