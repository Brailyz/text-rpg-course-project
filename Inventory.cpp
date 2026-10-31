#include "Inventory.hpp"

#include <iostream>

Inventory::Inventory()
    : m_items{ new Item * [2] {} }
    , m_size{ 0 }
    , m_capacity{ 2 }
{
    std::cout << "Inventory has been created\n";
}

Inventory::~Inventory()
{
    delete[] m_items;

    std::cout << "Destroying inventory...\n";
}

void Inventory::Resize()
{
    const auto newCapacity = m_capacity * 2;

    auto** newItems = new Item * [newCapacity] {};

    for (std::int32_t i = 0; i < m_size; ++i)
    {
        newItems[i] = m_items[i];
    }

    delete[] m_items;

    m_items = newItems;
    m_capacity = newCapacity;
}

void Inventory::AddItem(Item* item)
{
    if (item == nullptr)
    {
        std::cout << "Can't add empty item\n";
        return;
    }

    if (HasItem(item))
    {
        std::cout << "Can't add item again: " << item->GetName() << '\n';
        return;
    }

    if (m_size >= m_capacity)
    {
        Resize();
    }

    m_items[m_size] = item;
    ++m_size;

    std::cout << "The item has been added to your inventory: " << item->GetName() << '\n';
}

void Inventory::RemoveItem(Item* item)
{
    for (std::int32_t i = 0; i < m_size; ++i)
    {
        if (m_items[i] == item)
        {
            for (std::int32_t j = i; j < m_size - 1; ++j)
            {
                m_items[j] = m_items[j + 1];
            }

            m_items[m_size - 1] = nullptr;
            --m_size;

            std::cout << "The item has been removed from the inventory.\n";
            return;
        }
    }

    std::cout << "The item is missing from the inventory\n";
}

void Inventory::UseItem(Item* item)
{
    if (!HasItem(item))
    {
        std::cout << "Item cannot be used: " << "его нет в инвентаре\n";
        return;
    }

    item->Use();
}

void Inventory::ShowItems() const
{
    std::cout << "Items in inventory: " << m_size << '\n';

    for (std::int32_t i = 0; i < m_size; ++i)
    {
        m_items[i]->ShowInfo();
    }
}

bool Inventory::HasItem(Item* item) const
{
    for (std::int32_t i = 0; i < m_size; ++i)
    {
        if (m_items[i] == item)
        {
            return true;
        }
    }

    return false;
}