#include "BaseItem.hpp"

#include <iostream>
#include <utility>

std::int32_t BaseItem::GenerateInventoryNumber()
{
    return s_nextInventoryNumber++;
}

BaseItem::BaseItem()
    : m_inventoryNumber{ GenerateInventoryNumber() }
    , m_name{ "Unnamed" }
    , m_description{}
{
    ++s_createdCount;
    std::cout << "[BaseItem] default constructor: #" << m_inventoryNumber << '\n';
}

BaseItem::BaseItem(const std::string& name, const std::string& description)
    : m_inventoryNumber{ GenerateInventoryNumber() }
    , m_name{ name }
    , m_description{ description }
{
    ++s_createdCount;
    std::cout << "[BaseItem] parameterized constructor: " << m_name << " #" << m_inventoryNumber << '\n';
}

BaseItem::BaseItem(const BaseItem& other)
    : m_inventoryNumber{ GenerateInventoryNumber() }
    , m_name{ other.m_name }
    , m_description{ other.m_description }
{
    ++s_createdCount;
    std::cout << "[BaseItem] copy constructor: " << m_name << " #" << m_inventoryNumber << '\n';
}

BaseItem::BaseItem(BaseItem&& other) noexcept
    : m_inventoryNumber{ other.m_inventoryNumber }
    , m_name{ std::move(other.m_name) }
    , m_description{ std::move(other.m_description) }
{
    other.m_inventoryNumber = 0;
    ++s_createdCount;
    std::cout << "[BaseItem] move constructor: " << m_name << " #" << m_inventoryNumber << '\n';
}

BaseItem& BaseItem::operator=(const BaseItem& other)
{
    std::cout << "[BaseItem] copy assignment\n";

    if (this != &other)
    {
        m_name = other.m_name;
        m_description = other.m_description;
    }

    return *this;
}

BaseItem& BaseItem::operator=(BaseItem&& other) noexcept
{
    std::cout << "[BaseItem] move assignment\n";

    if (this != &other)
    {
        m_name = std::move(other.m_name);
        m_description = std::move(other.m_description);
    }

    return *this;
}

BaseItem::~BaseItem()
{
    std::cout << "[BaseItem] destructor: " << m_name << " #" << m_inventoryNumber << '\n';
}

void BaseItem::Describe() const
{
    std::cout << GetTitle() << '\n';
    std::cout << "  Description: " << m_description << '\n';
}

const std::string& BaseItem::GetName() const
{
    return m_name;
}

const std::string& BaseItem::GetDescription() const
{
    return m_description;
}

std::int32_t BaseItem::GetInventoryNumber() const
{
    return m_inventoryNumber;
}

BaseItem& BaseItem::SetDescription(const std::string& description)
{
    m_description = description;
    return *this;
}

// Конкатенация
std::string BaseItem::GetTitle() const
{
    return "[" + GetTypeName() + "] " + m_name + " #" + std::to_string(m_inventoryNumber);
}

// Поиск 
bool BaseItem::DescriptionContains(const std::string& word) const
{
    return m_description.find(word) != std::string::npos;
}

// Выделение подстроки 
std::string BaseItem::GetShortDescription(std::size_t length) const
{
    if (m_description.size() <= length)
    {
        return m_description;
    }

    return m_description.substr(0, length) + "...";
}

// Сравнение
bool BaseItem::HasSameName(const BaseItem& other) const
{
    return m_name.compare(other.m_name) == 0;
}

std::int32_t BaseItem::GetCreatedCount()
{
    return s_createdCount;
}
