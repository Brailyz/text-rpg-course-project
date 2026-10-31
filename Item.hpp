#pragma once

#include <string>
#include <string_view>

class Item
{
private:
	std::string m_name;
	std::string m_description;

public:
	Item();
	Item(std::string_view name, std::string_view description);
	~Item();

	[[nodiscard]] std::string_view GetName() const;

	[[nodiscard]] std::string_view GetDescription() const;

	void Set(std::string_view name, std::string_view description);

	void Use();
	void ShowInfo() const;
};