#include "Inventory.hpp"

#include "Character.hpp"
#include "GameExceptions.hpp"

#include <iostream>
#include <stdexcept>
#include <utility>

Inventory::Inventory(const Character& owner)
    : m_owner{ owner }
    , m_items{ std::make_unique<std::shared_ptr<BaseItem>[]>(2) }
    , m_size{ 0 }
    , m_capacity{ 2 }
{
    std::cout << "Inventory has been created\n";
}

Inventory::~Inventory() noexcept
{
    std::cout << "Destroying inventory...\n";
}

void Inventory::Resize()
{
    const auto newCapacity = m_capacity * 2;
    auto newItems = std::make_unique<std::shared_ptr<BaseItem>[]>(newCapacity);

    for (std::int32_t i = 0; i < m_size; ++i)
    {
        newItems[i] = std::move(m_items[i]);
    }

    m_items = std::move(newItems);
    m_capacity = newCapacity;
}

void Inventory::AddItem(const std::shared_ptr<BaseItem>& item)
{
    if (item == nullptr)
    {
        throw std::invalid_argument{ "Can't add empty item" };
    }

    if (HasItem(item.get()))
    {
        throw DuplicateItemException{ item->GetName() };
    }

    if (m_size >= m_capacity)
    {
        Resize();
    }

    m_items[m_size] = item;
    ++m_size;

    std::cout << "The item has been added to your inventory: " << item->GetName() << '\n';
}

void Inventory::RemoveItem(const BaseItem* item)
{
    if (item == nullptr)
    {
        throw std::invalid_argument{ "Can't remove empty item" };
    }

    for (std::int32_t i = 0; i < m_size; ++i)
    {
        if (m_items[i].get() == item)
        {
            for (std::int32_t j = i; j < m_size - 1; ++j)
            {
                m_items[j] = m_items[j + 1];
            }

            m_items[m_size - 1].reset();
            --m_size;

            std::cout << "The item has been removed from the inventory.\n";
            return;
        }
    }

    throw ItemNotInInventoryException{ item->GetName() };
}

void Inventory::UseItem(const BaseItem* item) const
{
    if (item == nullptr)
    {
        throw std::invalid_argument{ "Can't use empty item" };
    }

    if (!HasItem(item))
    {
        throw ItemNotInInventoryException{ item->GetName() };
    }

    item->Use();
}

void Inventory::ShowItems() const
{
    std::cout << m_owner.GetName() << "'s inventory, items: " << m_size << '\n';

    for (std::int32_t i = 0; i < m_size; ++i)
    {
        m_items[i]->Describe();
    }
}

bool Inventory::HasItem(const BaseItem* item) const
{
    if (item == nullptr)
    {
        return false;
    }

    for (std::int32_t i = 0; i < m_size; ++i)
    {
        if (m_items[i].get() == item)
        {
            return true;
        }
    }

    return false;
}