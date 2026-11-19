using System;
using System.Xml.Linq;

namespace Lab04
{
    internal class Weapon : BaseItem
    {
        public int Damage { get; }

        public ItemEffect Effect { get; }

        public Weapon(string name, string description, int damage, ItemEffect effect)
            : base(name, description)
        {
            Damage = damage < 0 ? 0 : damage;
            Effect = effect ?? new ItemEffect("Нет", 0);

            Console.WriteLine($"Оружие {Name} готово: урон {Damage}.");
        }

        // Конструктор копирования (глубокое копирование)
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

        public Weapon SetEffectPower(int power)
        {
            Effect.Power = power;
            return this;
        }
    }
}
