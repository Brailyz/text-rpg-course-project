#include "Potion.hpp"

#include "GameExceptions.hpp"

#include <iostream>

Potion::Potion()
    : BaseItem{}
    , m_healAmount{ 0 }
    , m_effect{ std::make_shared<ItemEffect>() }
{
    std::cout << "[Potion] default constructor\n";
}

Potion::Potion(const std::string& name, const std::string& description,
    std::int32_t healAmount, const ItemEffect& effect)
    : BaseItem{ name, description }
    , m_healAmount{ healAmount }
    , m_effect{ std::make_shared<ItemEffect>(effect) }
{
    std::cout << "[Potion] parameterized constructor: heals " << m_healAmount << '\n';
}

Potion::~Potion() noexcept
{
    std::cout << "[Potion] destructor: " << m_name << '\n';
}

void Potion::Use() const
{
    std::cout << "You drink " << m_name << ": +" << m_healAmount << " health\n";
}

void Potion::Describe() const
{
    std::cout << "Potion " << m_name << " heals " << m_healAmount;

    if (m_effect != nullptr)
    {
        std::cout << ", effect: " << m_effect->name << " (power " << m_effect->power
            << ", shared by " << m_effect.use_count() << " owner(s))";
    }

    std::cout << '\n';
}

std::unique_ptr<BaseItem> Potion::Clone() const
{
    return std::make_unique<Potion>(*this);
}

std::string Potion::GetTypeName() const
{
    return "Potion";
}

std::int32_t Potion::GetPrice() const
{
    return m_healAmount * PRICE_PER_HEAL;
}

bool Potion::IsSold() const
{
    return m_sold;
}

void Potion::Sell(std::string_view buyer)
{
    if (m_sold)
    {
        throw ItemAlreadySoldException{ m_name };
    }

    m_sold = true;
    std::cout << m_name << " sold to " << buyer << " for " << GetPrice() << " gold\n";
}

void Potion::SetEffectPower(std::int32_t power)
{
    if (m_effect != nullptr)
    {
        m_effect->power = power;
    }
}

long Potion::GetEffectUseCount() const
{
    return m_effect.use_count();
}