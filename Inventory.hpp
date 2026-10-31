#pragma once

#include "Item.hpp"

#include <cstdint>
#include <memory>

class Inventory
{
private:
	std::unique_ptr<std::shared_ptr<Item>[]> m_items;
	std::int32_t m_size;
	std::int32_t m_capacity;

	void Resize();

public:
	Inventory();
	~Inventory();

	Inventory(const Inventory&) = delete;
	Inventory(Inventory&&) = delete;
	Inventory& operator=(const Inventory&) = delete;
	Inventory& operator=(Inventory&&) = delete;

	void AddItem(const std::shared_ptr<Item>& item);

	void RemoveItem(Item* item);
	bool UseItem(Item* item);

	void ShowItems() const;

	[[nodiscard]] bool HasItem(const Item* item) const;
};