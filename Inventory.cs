using System;
using System.Text;

namespace Lab03
{
    internal class Inventory
    {
        private Item[] _items;

        private int _size = 0;

        private int _capacity = 1;

        public Inventory()
        {
            _items = new Item[_capacity];

            Console.WriteLine("Инвентарь создан.");
        }

        private void Resize()
        {
            int newCapacity = _capacity * 2;

            Array.Resize(ref _items, newCapacity);

            _capacity = newCapacity;
        }

        public void AddItem(Item item)
        {
            if (item == null)
            {
                Console.WriteLine("Нельзя добавить пустой предмет.");
                return;
            }

            if (HasItem(item))
            {
                Console.WriteLine($"Нельзя добавить предмет снова: {item.Name}.");
                return;
            }

            if (_size >= _capacity)
            {
                Resize();
            }

            _items[_size++] = item;

            Console.WriteLine($"Предмет добавлен в инвентарь: {item.Name}");
        }

        public void RemoveItem(Item item)
        {
            for (int i = 0; i < _size; i++)
            {
                if (_items[i] == item)
                {
                    for (int j = i; j < _size - 1; j++)
                    {
                        _items[j] = _items[j + 1];
                    }

                    _items[_size - 1] = null;
                    _size--;

                    Console.WriteLine($"Предмет {item.Name} удален из инвентаря.");

                    return;
                }

            }
                Console.WriteLine("Предмета нет в инвентаре.");
        }

        public void UseItem(Item item)
        {
            if (!HasItem(item))
            {
                Console.WriteLine("Предмета нет в инвентаре.");
                return;
            }

            item.Use();
        }

        private bool HasItem(Item item)
        {
            for (int i = 0; i < _size; i++)
            {
                if (_items[i] == item)
                {
                    return true;
                }
            }

            return false;
        }

        public override string ToString()
        {
            var sb = new StringBuilder();

            sb.AppendLine($"Предметов в инвентаре: {_size}");

            for (int i = 0; i < _size; i++)
            {
                sb.AppendLine(_items[i].ToString());
            }

            return sb.ToString();
        }
    }
}
