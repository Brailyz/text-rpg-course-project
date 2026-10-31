using System;

namespace Lab03
{
    internal class Item
    {
        public string Name { get; }

        public string Description { get; }

        public Item(string name, string description)
        {
            Name = name;
            Description = description;

            Console.WriteLine($"Предмет {Name} создан.");
        }

        ~Item()
        {
            Console.WriteLine($"Предмет {Name} уничтожен сборщиком мусора.");
        }

        public void Use()
        {
            Console.WriteLine($"Предмет {Name} использован.");
        }

        public override string ToString()
        {
            return $"Предмет: {Name}, Описание: {Description}";
        }
    }
}
