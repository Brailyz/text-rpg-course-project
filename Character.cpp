#include "Character.hpp"

#include <iostream>

Character::Character(std::string_view name, std::int32_t health, std::int32_t maxHealth)
    : m_name{ name }
    , m_health{ health }
    , m_maxHealth{ maxHealth }
{
    if (maxHealth <= 0 || health <= 0)
    {
        std::cout << "Health must be positive\n";
        m_maxHealth = 1;
        m_health = 1;
    }
}

Character::~Character()
{
    std::cout << "Destroying character: " << m_name << '\n';
}

std::string_view Character::GetName() const
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
        std::cout << "Damage must be positive\n";
        return;
    }

    m_health -= damage;

    if (m_health < 0)
    {
        m_health = 0;
    }

    std::cout << m_name << " takes damage: " << damage << '\n';
}

void Character::AddItem(Item* item)
{
    m_inventory.AddItem(item);
}

void Character::UseItem(Item* item)
{
    m_inventory.UseItem(item);
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