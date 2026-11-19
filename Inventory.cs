using System;
using System.Text;
using ItemList = System.Collections.Generic.List<Lab04.BaseItem>;

namespace Lab04
{
    internal class Inventory
    {
        private readonly Character _owner;

        private readonly ItemList _items;

        public Inventory(Character owner)
        {
            _owner = owner;
            _items = new ItemList();

            Console.WriteLine("Инвентарь создан.");
        }

        public void AddItem(BaseItem item)
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

            _items.Add(item);

            Console.WriteLine($"Предмет добавлен в инвентарь: {item.Name}");
        }

        public void RemoveItem(BaseItem item)
        {
            if (_items.Remove(item))
            {
                Console.WriteLine($"Предмет {item.Name} удален из инвентаря.");
            }
            else
            {
                Console.WriteLine("Предмета нет в инвентаре.");
            }
        }

        public void UseItem(BaseItem item)
        {
            if (!HasItem(item))
            {
                Console.WriteLine("Предмета нет в инвентаре.");
                return;
            }

            item.Use();
        }

        private bool HasItem(BaseItem item)
        {
            return _items.Contains(item);
        }

        public override string ToString()
        {
            var sb = new StringBuilder();

            sb.AppendLine($"Инвентарь персонажа {_owner.Name}. Предметов: {_items.Count}");

            foreach (BaseItem item in _items)
            {
                sb.AppendLine(item.ToString());
            }

            return sb.ToString();
        }
    }
}
