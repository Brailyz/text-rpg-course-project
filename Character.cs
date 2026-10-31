using System;

namespace Lab03
{
    internal class Character
    {
        private readonly Inventory _inventory;

        public string Name { get; }

        public int MaxHealth { get; }

        public int Health { get; private set; }

        public Character(string name, int health, int maxHealth)
        {
            Name = name;

            if (maxHealth <= 0 || health <= 0)
            {
                Console.WriteLine("Здоровье должно быть положительным.");

                maxHealth = 1;
                health = 1;
            }

            if (health > maxHealth)
            {
                Console.WriteLine("Здоровье не может превышать максимальное здоровье.");

                health = maxHealth;
            }

            MaxHealth = maxHealth;

            Health = health;

            Console.WriteLine($"Персонаж {Name} создан.");

            _inventory = new Inventory();
        }

        public void TakeDamage(int damage)
        {
            if (damage < 0)
            {
                Console.WriteLine("Урон не может быть отрицательным.");
                return;
            }

            Health -= damage;

            if (Health < 0)
            {
                Health = 0;
            }

            Console.WriteLine($"{Name} получает урон в размере {damage}!");
        }

        public void AddItem(Item item)
        {
            _inventory.AddItem(item);
        }

        public void RemoveItem(Item item)
        {
            _inventory.RemoveItem(item);
        }

        public void UseItem(Item item)
        {
            _inventory.UseItem(item);
        }

        public override string ToString()
        {
            return $"Персонаж: {Name}, Здоровье: {Health}/{MaxHealth}";
        }

        public string GetInventoryInfo()
        {
            return _inventory.ToString();
        }
    }
}
