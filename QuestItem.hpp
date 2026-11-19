#pragma once

#include "BaseItem.hpp"

#include <memory>
#include <string>

class QuestItem final : public BaseItem
{
public:
    QuestItem(const std::string& name, const std::string& description);
    QuestItem(const QuestItem& other) = default;
    ~QuestItem() noexcept override;

    void Use() const override;
    [[nodiscard]] std::unique_ptr<BaseItem> Clone() const override;
    [[nodiscard]] std::string GetTypeName() const override;
};