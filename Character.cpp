#include "Character.hpp"

#include "DamagePolicies.hpp"
#include "GameExceptions.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>

Character::Character(const std::string& name, std::int32_t health, std::int32_t maxHealth)
    : m_name{ name }
    , m_health{ health }
    , m_maxHealth{ maxHealth }
    , m_inventory{ *this }
    , m_policy{ std::make_unique<NoProtection>() }
{
    if (maxHealth <= 0 || health <= 0 || health > maxHealth)
    {
        throw InvalidHealthException{ health, maxHealth };
    }
}

Character::~Character() noexcept
{
    std::cout << "Destroying character: " << m_name << '\n';
}

const std::string& Character::GetName() const
{
    return m_name;
}

std::int32_t Character::GetHealth() const
{
    return m_health;
}

std::int32_t Character::GetMaxHealth() const
{
    return m_maxHealth;
}

void Character::TakeDamage(std::int32_t damage)
{
    if (damage < 0)
    {
        throw InvalidDamageException{ damage };
    }

    const auto realDamage = m_policy->Reduce(damage);
    m_health = std::max(0, m_health - realDamage);

    std::cout << m_name << " takes damage: " << damage << " -> " << realDamage
        << " (" << m_policy->GetName() << "), health " << m_health << '\n';
}

void Character::SetDamagePolicy(std::unique_ptr<IDamagePolicy> policy)
{
    if (policy == nullptr)
    {
        throw std::invalid_argument{ "Damage policy must not be empty" };
    }

    m_policy = std::move(policy);
}

void Character::AddItem(const std::shared_ptr<BaseItem>& item)
{
    m_inventory.AddItem(item);
}

void Character::RemoveItem(const BaseItem* item)
{
    m_inventory.RemoveItem(item);
}

void Character::UseItem(const std::shared_ptr<BaseItem>& item)
{
    if (item == nullptr)
    {
        throw std::invalid_argument{ "Can't use empty item" };
    }

    m_inventory.UseItem(item.get());  
    m_lastUsedItem = item;
}

void Character::ShowLastUsedItem() const
{
    if (const auto item = m_lastUsedItem.lock())
    {
        std::cout << "Last used item is still alive: " << item->GetName() << '\n';
    }
    else
    {
        std::cout << "Last used item no longer exists\n";
    }
}

void Character::ShowInventory() const
{
    m_inventory.ShowItems();
}

void Character::ShowInfo() const
{
    std::cout << "Character: " << m_name << '\n';
    std::cout << "Health: " << m_health << '/' << m_maxHealth << '\n';
}