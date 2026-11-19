#include "Weapon.hpp"

#include "GameExceptions.hpp"

#include <iostream>
#include <utility>

std::unique_ptr<ItemEffect> Weapon::CopyEffect(const ItemEffect* source)
{
    if (source == nullptr)
    {
        return nullptr;
    }

    return std::make_unique<ItemEffect>(*source);
}

Weapon::Weapon()
    : BaseItem{}
    , m_damage{ 0 }
    , m_effect{ std::make_unique<ItemEffect>() }
{
    std::cout << "[Weapon] default constructor\n";
}

Weapon::Weapon(const std::string& name, const std::string& description,
    std::int32_t damage, const ItemEffect& effect)
    : BaseItem{ name, description }
    , m_damage{ damage }
    , m_effect{ std::make_unique<ItemEffect>(effect) }
{
    std::cout << "[Weapon] parameterized constructor: damage " << m_damage << '\n';
}

Weapon::Weapon(const Weapon& other)
    : BaseItem{ other }
    , m_damage{ other.m_damage }
    , m_effect{ CopyEffect(other.m_effect.get()) }
{
    std::cout << "[Weapon] copy constructor (deep copy of effect)\n";
}

Weapon::Weapon(Weapon&& other) noexcept
    : BaseItem{ std::move(other) }
    , m_damage{ other.m_damage }
    , m_effect{ std::move(other.m_effect) }
{
    std::cout << "[Weapon] move constructor\n";
}

Weapon::~Weapon() noexcept
{
    std::cout << "[Weapon] destructor: " << m_name << '\n';
}

Weapon& Weapon::operator=(const Weapon& other)
{
    std::cout << "[Weapon] copy assignment\n";

    if (this == &other)
    {
        std::cout << "[Weapon] self-assignment detected, nothing to do\n";
        return *this;
    }

    BaseItem::operator=(other);
    m_damage = other.m_damage;
    m_effect = CopyEffect(other.m_effect.get());

    return *this;
}

Weapon& Weapon::operator=(Weapon&& other) noexcept
{
    std::cout << "[Weapon] move assignment\n";

    if (this != &other)
    {
        BaseItem::operator=(std::move(other));
        m_damage = other.m_damage;
        m_effect = std::move(other.m_effect);
    }

    return *this;
}

void Weapon::Use() const
{
    std::cout << "You strike with " << m_name << " for " << m_damage << " damage";

    if (m_effect != nullptr)
    {
        std::cout << " (+" << m_effect->power << ' ' << m_effect->name << ')';
    }

    std::cout << '\n';
}

void Weapon::Describe() const
{
    BaseItem::Describe();
    std::cout << "  Damage: " << m_damage;

    if (m_effect != nullptr)
    {
        std::cout << ", effect: " << m_effect->name << " (power " << m_effect->power << ')';
    }

    std::cout << '\n';
}

std::unique_ptr<BaseItem> Weapon::Clone() const
{
    return std::make_unique<Weapon>(*this);
}

std::string Weapon::GetTypeName() const
{
    return "Weapon";
}

std::int32_t Weapon::GetPrice() const
{
    return m_damage * PRICE_PER_DAMAGE;
}

bool Weapon::IsSold() const
{
    return m_sold;
}

void Weapon::Sell(std::string_view buyer)
{
    if (m_sold)
    {
        throw ItemAlreadySoldException{ m_name };
    }

    m_sold = true;
    std::cout << m_name << " sold to " << buyer << " for " << GetPrice() << " gold\n";
}

void Weapon::SetEffectPower(std::int32_t power)
{
    if (m_effect != nullptr)
    {
        m_effect->power = power;
    }
}

std::int32_t Weapon::GetEffectPower() const
{
    return m_effect != nullptr ? m_effect->power : 0;
}