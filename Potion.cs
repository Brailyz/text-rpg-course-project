using Lab05;
using System;
using System.Xml.Linq;

namespace Lab05
{
    internal sealed class Potion : BaseItem, ISellable
    {
        private const int PricePerHeal = 2;

        public int HealAmount { get; private set; }

        public ItemEffect Effect { get; }

        public bool IsSold { get; private set; }

        public int Price => HealAmount * PricePerHeal;

        public Potion(string name, string description, int healAmount, ItemEffect effect)
            : base(name, description)
        {
            HealAmount = healAmount < 0 ? 0 : healAmount;
            Effect = effect ?? new ItemEffect("Нет", 0);

            Console.WriteLine($"Зелье {Name} готово: лечит {HealAmount}.");
        }

        public override void Use()
        {
            Console.WriteLine($"Зелье {Name} выпито: +{HealAmount} здоровья.");
        }

        public override BaseItem Clone()
        {
            var copy = (Potion)ShallowCopy();
            copy.IsSold = false; 
            return copy;
        }

        public override string Describe()
        {
            return $"Зелье {Name} №{InventoryNumber}: лечит {HealAmount}, эффект: {Effect}";
        }

        public void Sell(string buyer)
        {
            if (IsSold)
            {
                throw new ItemAlreadySoldException(Name);
            }

            IsSold = true;
            Console.WriteLine($"{Name} продан покупателю {buyer} за {Price} золота.");
        }

        public void Dilute()
        {
            Description += " (разбавлено)";
            HealAmount /= 2;
        }
    }
}