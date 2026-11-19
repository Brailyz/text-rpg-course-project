#include "QuestItem.hpp"

#include <iostream>

QuestItem::QuestItem(const std::string& name, const std::string& description)
    : BaseItem{ name, description }
{
    std::cout << "[QuestItem] parameterized constructor\n";
}

QuestItem::~QuestItem() noexcept
{
    std::cout << "[QuestItem] destructor: " << m_name << '\n';
}

void QuestItem::Use() const
{
    std::cout << "You inspect " << m_name << ": it must be useful somewhere\n";
}

std::unique_ptr<BaseItem> QuestItem::Clone() const
{
    return std::make_unique<QuestItem>(*this);
}

std::string QuestItem::GetTypeName() const
{
    return "QuestItem";
}
