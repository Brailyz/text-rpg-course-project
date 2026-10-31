#include "Item.hpp"

#include <iostream>

Item::Item() = default;

Item::Item(std::string_view name, std::string_view description)
	: m_name{ name }
	, m_description{ description }
{}

Item::~Item()
{
	std::cout << "Destroying item: " << m_name << '\n';
}

std::string_view Item::GetName() const
{
	return m_name;
}

std::string_view Item::GetDescription() const
{
	return m_description;
}

void Item::Set(std::string_view name, std::string_view description)
{
	m_name = name;
	m_description = description;
}

void Item::Use()
{
	std::cout << "Item used: " << m_name << '\n';
}

void Item::ShowInfo() const
{
	std::cout << "Item: " << m_name << '\n';
	std::cout << "Description: " << m_description << '\n';
}