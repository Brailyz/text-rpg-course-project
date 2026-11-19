using System;

namespace Lab05
{
    internal class GameRuleException : Exception
    {
        public GameRuleException(string message) : base(message)
        {
        }
    }

    internal sealed class InvalidHealthException : GameRuleException
    {
        public InvalidHealthException(int health, int maxHealth)
            : base($"Недопустимое здоровье: {health}/{maxHealth}.")
        {
        }
    }

    internal sealed class InvalidDamageException : GameRuleException
    {
        public InvalidDamageException(int damage)
            : base($"Урон не может быть отрицательным: {damage}.")
        {
        }
    }

    internal sealed class DuplicateItemException : GameRuleException
    {
        public DuplicateItemException(string itemName)
            : base($"Предмет уже есть в инвентаре: {itemName}.")
        {
        }
    }

    internal sealed class ItemNotInInventoryException : GameRuleException
    {
        public ItemNotInInventoryException(string itemName)
            : base($"Предмета нет в инвентаре: {itemName}.")
        {
        }
    }

    internal sealed class ItemAlreadySoldException : GameRuleException
    {
        public ItemAlreadySoldException(string itemName)
            : base($"Предмет уже продан: {itemName}.")
        {
        }
    }

    internal sealed class NotSellableException : GameRuleException
    {
        public NotSellableException(string itemName)
            : base($"Предмет нельзя продать: {itemName}.")
        {
        }
    }
}