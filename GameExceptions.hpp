#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

class InvalidHealthException : public std::logic_error
{
public:
    InvalidHealthException(std::int32_t health, std::int32_t maxHealth)
        : std::logic_error{ "Invalid health: " + std::to_string(health) + '/' + std::to_string(maxHealth) }
    {}
};

class InvalidDamageException : public std::logic_error
{
public:
    explicit InvalidDamageException(std::int32_t damage)
        : std::logic_error{ "Damage must not be negative: " + std::to_string(damage) }
    {}
};

class DuplicateItemException : public std::runtime_error
{
public:
    explicit DuplicateItemException(const std::string& itemName)
        : std::runtime_error{ "Item is already in the inventory: " + itemName }
    {}
};

class ItemNotInInventoryException : public std::runtime_error
{
public:
    explicit ItemNotInInventoryException(const std::string& itemName)
        : std::runtime_error{ "Item is not in the inventory: " + itemName }
    {}
};

class ItemAlreadySoldException : public std::runtime_error
{
public:
    explicit ItemAlreadySoldException(const std::string& itemName)
        : std::runtime_error{ "Item is already sold: " + itemName }
    {}
};

class NotSellableException : public std::runtime_error
{
public:
    explicit NotSellableException(const std::string& itemName)
        : std::runtime_error{ "Item cannot be sold: " + itemName }
    {}
};
