using System;

namespace Lab04
{
    internal class ItemEffect
    {
        public string Name { get; set; }

        public int Power { get; set; }

        public ItemEffect(string name, int power)
        {
            Name = name;
            Power = power;
        }

        // Конструктор копирования
        public ItemEffect(ItemEffect other) : this(other.Name, other.Power)
        {
        }

        public override string ToString()
        {
            return $"{Name} (сила {Power})";
        }
    }
}
