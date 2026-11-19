using System;

namespace Lab05
{
    internal abstract class BaseItem : IComparable<BaseItem>
    {
        private static int _nextInventoryNumber = 1000;

        private static int _createdCount = 0;

        public string Name { get; }

        public string Description { get; protected set; }

        public int InventoryNumber { get; private set; }

        protected BaseItem(string name, string description)
        {
            Name = name;
            Description = description;
            InventoryNumber = GenerateInventoryNumber();
            _createdCount++;

            Console.WriteLine($"Предмет {Name} создан (№{InventoryNumber}).");
        }

        protected BaseItem(BaseItem other) : this(other.Name, other.Description)
        {
        }

        ~BaseItem()
        {
            Console.WriteLine($"Предмет {Name} уничтожен сборщиком мусора.");
        }

        public static int GetCreatedCount()
        {
            return _createdCount;
        }

        private static int GenerateInventoryNumber()
        {
            return _nextInventoryNumber++;
        }

        public abstract void Use();

        public abstract BaseItem Clone();

        public virtual string Describe()
        {
            return $"[{GetType().Name}] {Name} №{InventoryNumber}: {Description}";
        }

        public string GetCategory()
        {
            return "предмет";
        }

        public sealed override string ToString()
        {
            return Describe();
        }

        protected BaseItem ShallowCopy()
        {
            var copy = (BaseItem)MemberwiseClone();
            copy.InventoryNumber = GenerateInventoryNumber();
            _createdCount++;

            Console.WriteLine($"Поверхностная копия предмета {Name} (№{copy.InventoryNumber}).");
            return copy;
        }

        public int CompareTo(BaseItem other)
        {
            if (other is null)
            {
                return 1;
            }

            return string.Compare(Name, other.Name, StringComparison.CurrentCulture);
        }

        public bool Equals(BaseItem other)
        {
            if (other is null)
            {
                return false;
            }

            if (ReferenceEquals(this, other))
            {
                return true;
            }

            return GetType() == other.GetType() && Name == other.Name;
        }

        public override bool Equals(object obj)
        {
            return Equals(obj as BaseItem);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(GetType(), Name);
        }
    }
}