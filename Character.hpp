#pragma once

#include "Inventory.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

class Character
{
private:
	std::string m_name;

	std::int32_t m_health;
	std::int32_t m_maxHealth;

	Inventory m_inventory;

	std::weak_ptr<Item> m_lastUsedItem;

public:
	Character(std::string_view name, std::int32_t health, std::int32_t maxHealth);
	~Character();

	Character(const Character&) = delete;
	Character(Character&&) = delete;
	Character& operator=(const Character&) = delete;
	Character& operator=(Character&&) = delete;

	[[nodiscard]] std::string_view GetName() const;

	[[nodiscard]] std::int32_t GetHealth() const;

	[[nodiscard]] std::int32_t GetMaxHealth() const;

	void TakeDamage(std::int32_t damage);
	void AddItem(const std::shared_ptr<Item>& item);
	void RemoveItem(Item* item);
	void UseItem(const std::shared_ptr<Item>& item);
	void ShowLastUsedItem() const;
	void ShowInventory() const;
	void ShowInfo() const;
};