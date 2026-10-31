#pragma once

#include "Item.hpp"

class Inventory
{
private:
    Item** m_items;
    std::int32_t m_size;
    std::int32_t m_capacity;

    void Resize();

public:
    Inventory();
    ~Inventory();

    Inventory(const Inventory&) = delete;
    Inventory(Inventory&&) = delete;
    Inventory& operator=(const Inventory&) = delete;
    Inventory& operator=(Inventory&&) = delete;

    void AddItem(Item* item);
    void RemoveItem(Item* item);
    void UseItem(Item* item);
    void ShowItems() const;

    [[nodiscard]] bool HasItem(Item* item) const;
};