using System;
using System.Xml.Linq;

namespace Lab04
{
    internal sealed class Potion : BaseItem
    {
        public int HealAmount { get; private set; }

        public ItemEffect Effect { get; }

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
            return ShallowCopy();
        }

        public override string Describe()
        {
            return $"Зелье {Name} №{InventoryNumber}: лечит {HealAmount}, эффект: {Effect}";
        }

        public void Dilute()
        {
            Description += " (разбавлено)";
            HealAmount /= 2;
        }
    }
}
