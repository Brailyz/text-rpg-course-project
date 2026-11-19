using System;

namespace Lab05
{
    internal class Character
    {
        private readonly Inventory _inventory;
        private IDamagePolicy _policy = new NoProtection();  

        public string Name { get; }

        public int MaxHealth { get; }

        public int Health { get; private set; }

        public IDamagePolicy Policy
        {
            get => _policy;
            set => _policy = value ?? throw new ArgumentNullException(nameof(value));
        }

        public Character(string name, int health, int maxHealth)
        {
            if (maxHealth <= 0 || health <= 0 || health > maxHealth)
            {
                throw new InvalidHealthException(health, maxHealth);
            }

            Name = name;
            MaxHealth = maxHealth;
            Health = health;

            Console.WriteLine($"Персонаж {Name} создан.");
            _inventory = new Inventory(this);
        }

        public void TakeDamage(int damage)
        {
            if (damage < 0)
            {
                throw new InvalidDamageException(damage);
            }

            int realDamage = _policy.Reduce(damage);
            Health = Math.Max(0, Health - realDamage);

            Console.WriteLine($"{Name} получает урон: {damage} -> {realDamage} ({_policy.Name}), здоровье {Health}.");
        }

        public void AddItem(BaseItem item)
        {
            _inventory.AddItem(item);
        }

        public void RemoveItem(BaseItem item)
        {
            _inventory.RemoveItem(item);
        }

        public void UseItem(BaseItem item)
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