#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

class BaseItem
{
private:
    inline static std::int32_t s_nextInventoryNumber{ 1000 };
    inline static std::int32_t s_createdCount{ 0 };

    std::int32_t m_inventoryNumber;

    [[nodiscard]] static std::int32_t GenerateInventoryNumber();

protected:
    std::string m_name;
    std::string m_description;

    BaseItem(const BaseItem& other);
    BaseItem(BaseItem&& other) noexcept;
    BaseItem& operator=(const BaseItem& other);
    BaseItem& operator=(BaseItem&& other) noexcept;

public:
    BaseItem();
    BaseItem(const std::string& name, const std::string& description);

    virtual ~BaseItem();

    virtual void Use() const = 0;
    [[nodiscard]] virtual std::unique_ptr<BaseItem> Clone() const = 0;
    [[nodiscard]] virtual std::string GetTypeName() const = 0;

    virtual void Describe() const;

    [[nodiscard]] const std::string& GetName() const;
    [[nodiscard]] const std::string& GetDescription() const;
    [[nodiscard]] std::int32_t GetInventoryNumber() const;

    BaseItem& SetDescription(const std::string& description);

    [[nodiscard]] std::string GetTitle() const;
    [[nodiscard]] bool DescriptionContains(const std::string& word) const;
    [[nodiscard]] std::string GetShortDescription(std::size_t length) const;
    [[nodiscard]] bool HasSameName(const BaseItem& other) const;

    [[nodiscard]] static std::int32_t GetCreatedCount();
};
