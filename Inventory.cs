using System;
using System.Text;
using ItemList = System.Collections.Generic.List<Lab05.BaseItem>;

namespace Lab05
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
                throw new ArgumentNullException(nameof(item), "Нельзя добавить пустой предмет.");
            }

            if (HasItem(item))
            {
                throw new DuplicateItemException(item.Name);
            }

            _items.Add(item);
            Console.WriteLine($"Предмет добавлен в инвентарь: {item.Name}");
        }

        public void RemoveItem(BaseItem item)
        {
            if (item == null)
            {
                throw new ArgumentNullException(nameof(item), "Нельзя удалить пустой предмет.");
            }

            if (!_items.Remove(item))
            {
                throw new ItemNotInInventoryException(item.Name);
            }

            Console.WriteLine($"Предмет {item.Name} удален из инвентаря.");
        }

        public void UseItem(BaseItem item)
        {
            if (item == null)
            {
                throw new ArgumentNullException(nameof(item), "Нельзя использовать пустой предмет.");
            }

            if (!HasItem(item))
            {
                throw new ItemNotInInventoryException(item.Name);
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
