
using Lab05;
using System;
using System.Xml.Linq;

namespace Lab05
{
    internal class Weapon : BaseItem, ISellable
    {
        private const int PricePerDamage = 10;

        public int Damage { get; }

        public ItemEffect Effect { get; }

        public bool IsSold { get; private set; }

        public int Price => Damage * PricePerDamage;

        public Weapon(string name, string description, int damage, ItemEffect effect)
            : base(name, description)
        {
            Damage = damage < 0 ? 0 : damage;
            Effect = effect ?? new ItemEffect("Нет", 0);

            Console.WriteLine($"Оружие {Name} готово: урон {Damage}.");
        }

        public Weapon(Weapon other) : base(other)
        {
            Damage = other.Damage;
            Effect = new ItemEffect(other.Effect);
        }

        public override void Use()
        {
            Console.WriteLine($"Удар: {Name}, урон {Damage} (+{Effect.Power} {Effect.Name}).");
        }

        public override BaseItem Clone()
        {
            return new Weapon(this);
        }

        public override string Describe()
        {
            return base.Describe() + $", урон: {Damage}, эффект: {Effect}";
        }

        public new string GetCategory()
        {
            return "оружие";
        }

        public void Sell(string buyer)
        {
            // проверка до изменения состояния
            if (IsSold)
            {
                throw new ItemAlreadySoldException(Name);
            }

            IsSold = true;
            Console.WriteLine($"{Name} продан покупателю {buyer} за {Price} золота.");
        }

        public Weapon SetEffectPower(int power)
        {
            Effect.Power = power;
            return this;
        }
    }
}
